/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_test_h
#define aw_test_test_h
#include <utility>
#include <functional>
#include <algorithm>
#include <exception>
#include <vector>
#include <string>
#include <iostream>
#include <aw/config.h>
#include <aw/utility/static_object.h>
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <cstdio>
#endif

/*!
 * This header is made for awlib internal tests.
 * It is so simple and crude, that it doesn't even
 * deserve separate directory.
 */

int main(int,char**);

namespace aw {
#if (AW_PLATFORM != AW_PLATFORM_WIN32)
char const bold[]  = "\033[1m";
char const red[]   = "\033[31m";
char const green[] = "\033[32m";
char const white[] = "\033[37m";
char const reset[] = "\033[0m";
#else
char const bold[]  = "";
char const red[]   = "";
char const green[] = "";
char const white[] = "";
char const reset[] = "";
#endif

namespace test {
enum class stage : size_t {
	start,
	setup,
	preconditions,
	checks,
	postconditions,
	end
};

static char const* stage_name[] {
	"start",
	"setup",
	"preconditions",
	"checks",
	"postconditions",
	"end"
};

struct test {
	using test_function = void();
	test(char const* name, test_function* func)
		: name{name}, func{func}
	{ }

	char const*    const name;

private:
	friend struct context;

	test_function* const func;

	stage st = stage::start;

	std::vector<std::string> messages;

	size_t failed   = 0;
	size_t succeded = 0;
};

struct test_failed : std::exception {};

template<typename...Args>
void print(Args&&...args)
{
	( std::cerr << ... << std::forward<Args>(args) );
}

template<typename...Args>
void println(Args&&...args)
{
	( std::cerr << ... << std::forward<Args>(args) ) << '\n';
}

namespace {
class context_check;
class context_block;
class register_test;
}

class registry {
	friend int ::main(int, char**);
	friend struct context;
	class _ctxs {
		friend class registry;
		std::vector<struct context*> ctxs;
	public:
		_ctxs() = default;
	};

	static void add(context& ctx)
	{
		auto& vec = static_object<_ctxs>::instance().ctxs;
		vec.push_back(&ctx);
	}

	inline static int run();
};

struct context {
	context(char const* filename)
		: filename(filename)
	{
		registry::add(*this);
	}

	test& current() { return *cur; }
	char const* const filename;

	int run()
	{
		install_handler();

		print(bold, '[', filename, ']', ' ', reset);
		print("running tests\n");

		for (size_t i = 0, e = tests.size(); i < e; ++i) {
			print(bold, '[', i+1, '/', e, ']', ' ', reset);
			run_test(tests[i]);
		}

		size_t succeded = tests.size() - failed;

		print(bold, '[', filename, ']', ' ', reset);
		print("tests done, failed: ");
		print(bold, (failed > 0 ? red : white), failed, reset);
		print(", succeeded: ");
		print(bold, (succeded > 0 ? green : white), succeded, reset);
		print(reset, '\n');

		return failed;
	}

private:
	friend class aw::test::context_check;
	friend class aw::test::context_block;
	friend class aw::test::register_test;

	inline static void segvhandler(int signum);

	void install_handler()
	{
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
		signal(SIGSEGV, segvhandler);
#endif
	}

	inline void run_test(test& tst);

	void enter(stage st)
	{
		if (cur->failed > 0)
			throw test_failed{};
		cur->st = st;
	}

	void test_failure();

	void add_test(test&& tst)
	{
		tests.push_back(std::move(tst));
	}

	void check_fail(std::string const& msg)
	{
		cur->messages.push_back(msg);
		++cur->failed;
	}

	void check_succeed(std::string const&)
	{
		++cur->succeded;
	}

private:
	test* cur;
	std::vector<test> tests;
	unsigned failed = 0;
};

int registry::run()
{
	auto& vec = static_object<_ctxs>::instance().ctxs;

	int res = 0;
	for (auto& ctx : vec)
		res += ctx->run();

	return res > 0xFF ? 0xFF : res;
}

void context::test_failure()
{
	++failed;

	print(bold, red, " failed: (", stage_name[size_t(cur->st)], ") ", reset);
	print(red, "failed: ", bold, cur->failed, reset);
	print(green, ", succeded: ", bold, cur->succeded, reset, '\n');

	for (auto msg : cur->messages)
		print(bold, red, "test failed: ", reset, msg, '\n');
}

void context::run_test(test& tst)
{
	cur = &tst;
	print("test \"", bold, cur->name, reset, '"');
	try {
		enter(stage::start);
		cur->func();
		enter(stage::end);
		print(bold, green, " succeded, checks: ", cur->succeded, reset, '\n');
		return;
	} catch (test_failed& ex) {
		test_failure();
	} catch (std::exception& e) {
		test_failure();
		print(bold, red, "exception: ", reset, e.what(), '\n');
	} catch (...) {
		test_failure();
		print(bold, red, "caught unknown exception", reset, '\n');
	}

	cur->messages.clear();
}

namespace {
extern context file_context;
}

void context::segvhandler(int signum)
{
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
	file_context.test_failure();
	print(bold, red, "caught SIGSEGV, aborting tests", reset, '\n');
	signal(signum, SIG_DFL);
	kill(getpid(), signum);
#endif
}

namespace {
class context_check {
	template<typename Evaluator, typename... Args>
	friend void check(Evaluator eval, Args&&... args);

	static void check_fail(std::string const& msg)
	{
		file_context.check_fail(msg);
	}
	static void check_succeed(std::string const& msg)
	{
		file_context.check_succeed(msg);
	}
};

class context_block {
	friend bool setup();
	friend bool preconditions();
	friend bool checks();
	friend bool postconditions();

	static void enter(stage st)
	{
		file_context.enter(st);
	}
};

class register_test {
protected:
	void add_test(test&& tst)
	{
		file_context.add_test(std::move(tst));
	}
};

bool setup()          { context_block::enter(stage::setup); return true; }
bool preconditions()  { context_block::enter(stage::preconditions); return true; }
bool checks()         { context_block::enter(stage::checks); return true; }
bool postconditions() { context_block::enter(stage::postconditions); return true; }

template<typename Evaluator, typename... Args>
void check(Evaluator eval, Args&&... args)
{
	eval(std::forward<Args>(args)...) ?
		context_check::check_succeed(eval.msg()) :
		context_check::check_fail(eval.msg());
}
} // namespace
} // namespace test
} // namespace aw

#include <aw/utility/to_string.h>
#include <aw/types/strip.h>

namespace aw {
namespace test {
struct equal {
	template<typename A, typename B>
	bool operator()(A const& got, B const& expected)
	{
		using aw::to_string;
		this->got      = to_string(got);
		this->expected = to_string(expected);
		return got == expected;
	}

	std::string msg()
	{
		using namespace std::string_literals;
		return "\""s + expected + "\" == \""s + got + "\""s;
	}

	std::string expected;
	std::string got;
};

struct equal_v {
	template<typename T, typename...Args>
	bool operator()(T&& arg, Args&&...args)
	{
		using aw::to_string;
		std::vector<remove_reference<T>> tmp = { arg, args... };
		auto it = std::adjacent_find( begin(tmp), end(tmp), std::not_equal_to<T>() );
		values = to_string(tmp);
		return it == end(tmp);
	}

	std::string msg()
	{
		using namespace std::string_literals;
		return "values: "s + values;
	}

	std::string values;
};

struct _assert {
	bool operator()(bool expr)
	{
		return expr;
	}

	std::string msg() { return {_msg}; }
	char const* _msg;
};
} // namespace test
} // namespace aw

#define TestFile(name) namespace aw { namespace test { namespace { context file_context{name}; } } }
#define Test(name)     \
	void run_test_##name(); \
	struct Add_test_##name : aw::test::register_test { \
		Add_test_##name() { \
			add_test(aw::test::test{#name, run_test_##name}); \
		} \
	} add_test_##name; \
	void run_test_##name()
#define Setup          if (aw::test::setup())
#define Preconditions  if (aw::test::preconditions())
#define Checks         if (aw::test::checks())
#define Postconditions if (aw::test::postconditions())
#define RunTests()     int main(int,char**) { return aw::test::registry::run(); }

#include <aw/utility/macro.h>
#define TestEqual(...) \
aw::test::check(aw::test::equal{}, __VA_ARGS__)
#define TestEqualV(...) \
aw::test::check(aw::test::equal_v{}, __VA_ARGS__)
#define TestAssert(...) \
aw::test::check(aw::test::_assert{"assert: " #__VA_ARGS__}, (__VA_ARGS__))

#endif//aw_test_test_h
