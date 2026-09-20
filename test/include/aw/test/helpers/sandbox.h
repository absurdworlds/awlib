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
#include <aw/process/posix/fork.h>
#include <aw/process/posix/alarm.h>

#include <sys/resource.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

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
	rlim_t address_space_limit = 0;
	rlim_t stack_limit = 0;
};

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

	// so that the child doesn't flush a copy of the parent's buffers
	fflush(nullptr);

	const auto handle = process::posix::fork([=]{
		if (limits.address_space_limit) {
			rlimit as{limits.address_space_limit, limits.address_space_limit};
			setrlimit(RLIMIT_AS, &as);
		}
		if (limits.stack_limit) {
			rlimit st{limits.stack_limit, limits.stack_limit};
			setrlimit(RLIMIT_STACK, &st);
		}
		// no core dumps for the deliberate crashes
		rlimit core{0, 0};
		setrlimit(RLIMIT_CORE, &core);

		if (limits.time_limit != std::chrono::seconds::zero())
			process::posix::current_process::alarm(limits.time_limit);

		int code = exit_success;
		try {
			func();
		} catch (std::bad_alloc&) {
			code = exit_bad_alloc;
		} catch (...) {
			code = exit_exception;
		}
		process::posix::current_process::exit_now(code);
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
