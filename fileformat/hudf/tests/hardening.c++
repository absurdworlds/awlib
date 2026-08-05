/*
 * Copyright (C) 2026  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
/*
 * Regression tests for malformed input: the HuDF parse entry points must
 * terminate on hostile data instead of hanging, exhausting memory, or
 * overflowing the stack.
 *
 * Each case is run in a forked child under a wall-clock alarm, an address
 * space limit and a stack limit, so a regression is reported as a failed
 * test instead of wedging the test suite.
 */
#include <aw/hudf/parser.h>
#include <aw/hudf/utility.h>

#include <aw/io/input_memory_stream.h>

#include <aw/test/test.h>

#include <string>
#include <string_view>

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <sys/resource.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#endif

TestFile("hudf::hardening");

namespace aw::hudf {
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
namespace {
enum class outcome {
	completed,   //!< parser returned on its own
	timed_out,   //!< infinite loop
	out_of_memory,
	crashed,     //!< stack overflow / other fatal signal
	threw,
};

std::string to_string(outcome o)
{
	switch (o) {
	case outcome::completed:     return "completed";
	case outcome::timed_out:     return "timed_out";
	case outcome::out_of_memory: return "out_of_memory";
	case outcome::crashed:       return "crashed";
	case outcome::threw:         return "threw";
	}
	return "?";
}

constexpr rlim_t address_space_limit = 256u << 20;
constexpr rlim_t stack_limit         =   1u << 20;
constexpr unsigned time_limit        = 5;

/*!
 * Nesting depth for the deep-recursion case.
 *
 * Linux honours the lowered RLIMIT_STACK below, but a platform which sizes
 * the main stack once at exec time (macOS) keeps its default. The depth is
 * therefore chosen to overflow that default rather than the limit we ask for.
 */
constexpr int nesting_depth = 200000;

/*!
 * Run \a func in a child process under resource limits.
 */
template <typename Func>
outcome run_sandboxed(Func func)
{
	constexpr auto exit_success   = 0;
	constexpr auto exit_bad_alloc = 3;
	constexpr auto exit_exception = 4;

	fflush(nullptr);

	pid_t pid = fork();
	if (pid == 0) {
		rlimit as{address_space_limit, address_space_limit};
		setrlimit(RLIMIT_AS, &as);
		rlimit st{stack_limit, stack_limit};
		setrlimit(RLIMIT_STACK, &st);
		// no core dumps for the deliberate crashes
		rlimit core{0, 0};
		setrlimit(RLIMIT_CORE, &core);

		alarm(time_limit);

		int code = exit_success;
		try {
			func();
		} catch (std::bad_alloc&) {
			code = exit_bad_alloc;
		} catch (...) {
			code = exit_exception;
		}
		_exit(code);
	}

	int status = 0;
	waitpid(pid, &status, 0);

	if (WIFSIGNALED(status)) {
		int sig = WTERMSIG(status);
		if (sig == SIGALRM)
			return outcome::timed_out;
		return outcome::crashed;
	}

	switch (WEXITSTATUS(status)) {
	case exit_success:   return outcome::completed;
	case exit_bad_alloc: return outcome::out_of_memory;
	default:             return outcome::threw;
	}
}

io::input_memory_stream stream_of(std::string_view text)
{
	return io::input_memory_stream{text.data(), text.data() + text.size()};
}

//! Parse a document, discarding the result.
//! Any parse error is fine, a hang or a crash is not.
void parse(std::string_view text)
{
	auto stream = stream_of(text);
	auto doc = hudf::parse_file(stream);
	(void)doc;
}
} // namespace

Test(c1_unterminated_string_terminates)
{
	TestEqual(run_sandboxed([] { parse("a = \"unterminated"); }),
		  outcome::completed);
	TestEqual(run_sandboxed([] { parse("[node\n\tkey = \"oops\n]"); }),
		  outcome::completed);

	// closing '"' swallowed by escape
	TestEqual(run_sandboxed([] { parse("a = \"esc\\\""); }),
		  outcome::completed);
}

Test(c2_trailing_invalid_token_terminates) {
	// default case of read_token()
	TestEqual(run_sandboxed([] { parse("a = #"); }),
		  outcome::completed);

	// '+'/'-' not followed by a digit
	TestEqual(run_sandboxed([] { parse("a = +"); }),
		  outcome::completed);
	TestEqual(run_sandboxed([] { parse("a = -"); }),
		  outcome::completed);

	// invalid token at the very end of the file, after valid data
	TestEqual(run_sandboxed([] { parse("[node\n\ta = 1\n]\n@"); }),
		  outcome::completed);
}

Test(c2_valid_input_still_parses) {
	auto stream = stream_of("[node\n\ta = 1\n\tb = \"str\"\n\tc = -2.5\n]");
	auto doc = hudf::parse_file(stream);

	Checks {
		auto& root = doc.root();
		TestEqual(root.children.size(), size_t(1));

		auto* node = root.find_child("node");
		TestAssert(node != nullptr);
		if (!node)
			return;

		TestEqual(node->children.size(), size_t(3));

		auto* a = node->find_child("a");
		TestAssert(a != nullptr);
		if (a)
			TestEqual(a->try_get<intmax_t>(0), intmax_t(1));

		auto* b = node->find_child("b");
		TestAssert(b != nullptr);
		if (b)
			TestEqual(b->try_get<std::string>(""), std::string("str"));

		auto* c = node->find_child("c");
		TestAssert(c != nullptr);
		if (c)
			TestEqual(c->try_get<double>(0.0), -2.5);
	}
}

Test(c3_skip_unclosed_node_terminates) {
	TestEqual(run_sandboxed([] {
		auto stream = stream_of("[node\n\ta = 1\n");
		auto val = hudf::find_value(stream, "missing");
		(void)val;
	}), outcome::completed);

	TestEqual(run_sandboxed([] {
		auto stream = stream_of("[a\n\t[b\n\t\tx = 1\n");
		auto n = hudf::find_node(stream, "zzz");
		(void)n;
	}), outcome::completed);

	// nested path lookup: find_node() skips the non-matching node
	TestEqual(run_sandboxed([] {
		auto stream = stream_of("[other\n\tx = 1\n[wanted\n\ty = 2\n]");
		auto val = hudf::find_value(stream, "wanted/y");
		(void)val;
	}), outcome::completed);
}

Test(c3_find_value_still_works) {
	Checks {
		{
			auto stream = stream_of("[skipped\n\ta = 1\n]\nb = 2\n");
			auto val = hudf::find_value(stream, "b");
			TestAssert(!val.empty());
			if (auto num = val.get<intmax_t>())
				TestEqual(*num, intmax_t(2));
		}
		{
			auto stream = stream_of("[skipped\n\ta = 1\n]\n[wanted\n\tb = 2\n]\n");
			auto val = hudf::find_value(stream, "wanted/b");
			TestAssert(!val.empty());
			if (auto num = val.get<intmax_t>())
				TestEqual(*num, intmax_t(2));
		}
	}
}

Test(c4_deep_nesting_terminates) {
	// just under the limit: still a well-formed document
	TestEqual(run_sandboxed([] {
		std::string text;
		for (size_t i = 0; i < max_nesting_depth - 1; ++i)
			text += "[a ";
		text.append(max_nesting_depth - 1, ']');
		parse(text);
	}), outcome::completed);

	TestEqual(run_sandboxed([] {
		std::string text;
		for (int i = 0; i < nesting_depth; ++i)
			text += "[a ";
		text.append(nesting_depth, ']');
		parse(text);
	}), outcome::completed);

	// same but with unterminated nodes
	TestEqual(run_sandboxed([] {
		std::string text;
		for (int i = 0; i < nesting_depth; ++i)
			text += "[a ";
		parse(text);
	}), outcome::completed);
}

Test(c7_junk_token_run_terminates) {
	// ']' with nothing open
	TestEqual(run_sandboxed([] {
		parse(std::string(nesting_depth, ']'));
	}), outcome::completed);

	// ... and trailing a well-formed node
	TestEqual(run_sandboxed([] {
		std::string text = "[a\n\tx = 1\n]";
		text.append(nesting_depth, ']');
		parse(text);
	}), outcome::completed);

	// a run of invalid tokens, separated so they do not lex as one
	TestEqual(run_sandboxed([] {
		std::string text;
		for (int i = 0; i < nesting_depth; ++i)
			text += "@ ";
		parse(text);
	}), outcome::completed);
}
#endif // AW_PLATFORM_POSIX
} // namespace aw::hudf
