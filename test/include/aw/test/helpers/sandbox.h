/*
 * Copyright (C) 2026  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_sandbox_h
#define aw_test_sandbox_h
#include <aw/config.h>

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <aw/process.h>
#include <aw/process/limits.h>
#include <aw/process/posix/fork.h>
#include <aw/process/posix/alarm.h>

#include <chrono>
#include <cstdio>
#include <new>
#include <string>

namespace aw::test {
//! How a function run by run_sandboxed() ended
enum class outcome {
	completed,     //!< returned on its own
	threw,         //!< escaped by an exception
	out_of_memory, //!< escaped by std::bad_alloc
	timed_out,     //!< ran past the time limit
	aborted,       //!< exited with abort or std::terminate
	crashed,       //!< any other fatal signal
};

inline std::string to_string(outcome o)
{
	switch (o) {
	case outcome::completed:     return "completed";
	case outcome::threw:         return "threw";
	case outcome::out_of_memory: return "out_of_memory";
	case outcome::timed_out:     return "timed_out";
	case outcome::aborted:       return "aborted";
	case outcome::crashed:       return "crashed";
	}
	return "?";
}

//! Resource limits for run_sandboxed(); zero means unlimited
struct sandbox {
	std::chrono::seconds time_limit = {};
	uintmax_t address_space_limit = 0;
	uintmax_t stack_limit = 0;
};

/*!
 * Adjust \a limits for the instrumentation the process is carrying.
 *
 * A sanitizer changes what these limits mean, in ways no caller can
 * usefully predict:
 *
 * - The runtime reserves terabytes of address space for its shadow
 *   memory, so any address-space limit small enough to be worth setting
 *   kills the child on its next mmap rather than on a runaway
 *   allocation. There is no figure that works; the limit is dropped.
 * - Instrumented frames are several times larger, so a stack limit
 *   chosen for the uninstrumented build overflows on the same recursion
 *   depth.
 * - Everything runs slower, ThreadSanitizer by an order of magnitude, so
 *   a time limit meant to catch a hang starts catching a slow success
 *   instead.
 *
 * The limits still do their job after this -- they are just loose enough
 * that only a genuine runaway reaches them.
 */
constexpr sandbox adjust_for_instrumentation(sandbox limits)
{
	if (!AW_SANITIZER_ANY)
		return limits;

	limits.address_space_limit = 0;
	limits.stack_limit *= 8;
	limits.time_limit  *= 12;
	return limits;
}

/*!
 * Run \a func in a child process, so that any crash is isolated from
 * the rest of the test suite.
 *
 * The child does not report anything back besides the outcome.
 */
template <typename Func>
outcome run_sandboxed(Func func, sandbox limits = {})
{
	constexpr auto exit_success   = 0;
	constexpr auto exit_bad_alloc = 3;
	constexpr auto exit_exception = 4;

	limits = adjust_for_instrumentation(limits);

	// so that the child doesn't flush a copy of the parent's buffers
	fflush(nullptr);

	const auto handle = process::posix::fork([=]{
		if (limits.address_space_limit)
			process::self::set_limit( process::resource::address_space, limits.address_space_limit );
		if (limits.stack_limit)
			process::self::set_limit( process::resource::stack, limits.stack_limit );

		// no core dumps for the deliberate crashes
		process::self::set_limit( process::resource::core_file, 0 );

		if (limits.time_limit != std::chrono::seconds::zero())
			process::posix::self::alarm(limits.time_limit);

		int code = exit_success;
		try {
			func();
		} catch (std::bad_alloc&) {
			code = exit_bad_alloc;
		} catch (...) {
			code = exit_exception;
		}
		process::posix::self::exit_now(code);
		return;
	});

	std::error_code ec;
	const auto result = process::wait(handle, ec);

	switch (result.signal) {
	case process::no_signal: break;
	case SIGALRM: return outcome::timed_out;
	case SIGABRT: return outcome::aborted;
	default:      return outcome::crashed;
	}

	switch (result.code) {
	case exit_success:   return outcome::completed;
	case exit_bad_alloc: return outcome::out_of_memory;
	default:             return outcome::threw;
	}
}
} // namespace aw::test
#endif // AW_PLATFORM_POSIX
#endif//aw_test_sandbox_h
