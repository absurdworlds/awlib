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
#include <aw/platform/demangle.h>
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
char const _bold[]  = "\033[1m";
char const _red[]   = "\033[31m";
char const _green[] = "\033[32m";
char const _white[] = "\033[37m";
char const _reset[] = "\033[0m";
inline std::ostream& bold(std::ostream& os)  { if (isatty(1)) os << _bold;  return os;}
inline std::ostream& red(std::ostream& os)   { if (isatty(1)) os << _red;   return os;}
inline std::ostream& green(std::ostream& os) { if (isatty(1)) os << _green; return os;}
inline std::ostream& white(std::ostream& os) { if (isatty(1)) os << _white; return os;}
inline std::ostream& reset(std::ostream& os) { if (isatty(1)) os << _reset; return os;}
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

struct check_report {
	explicit operator bool() const { return status; }
	bool status;
	std::string message;
};

struct test {
	using test_function = void();
	test(char const* name, test_function* func)
		: name{name}, func{func}
	{ }

	char const* const name;

private:
	friend struct context;

	test_function* const func;

	stage st = stage::start;

	std::vector<check_report> checks;
};

struct test_failed : std::exception {};

template<typename...Args>
void print(Args&&...args)
{
	( std::cout << ... << std::forward<Args>(args) );
}

template<typename...Args>
void println(Args&&...args)
{
	( std::cout << ... << std::forward<Args>(args) ) << '\n';
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


class report {
public:
	virtual void begin_suite(const char* name, int test_count) = 0;
	virtual void end_suite() = 0;

	virtual void test_success(const char* name, const std::vector<check_report>& checks) = 0;
	virtual void test_failure(const char* name, const std::vector<check_report>& checks, const char* detail) = 0;
};

class report_classic : public report {
public:
	void begin_suite(const char* name, int test_count) override
	{
		filename = name;
		total    = test_count;

		println(bold, '[', filename, ']', ' ', reset, "running tests");
	}

	void end_suite()
	{
		print(bold, '[', filename, ']', ' ', reset);
		print("tests done, failed: ");
		print(bold, (failed > 0 ? red : white), failed, reset);
		print(", succeeded: ");
		print(bold, (succeeded > 0 ? green : white), succeeded, reset);
		print(reset, '\n');

	}

	void test_success(const char* name, const std::vector<check_report>& checks) override
	{
		++succeeded;

		test_start(name);

		println(bold, green, " succeeded, checks: ", checks.size(), reset);
	}

	void test_failure(const char* name, const std::vector<check_report>& checks, const char* detail) override
	{
		++failed;

		test_start(name);

		int checks_failed    = 0;
		int checks_succeeded = 0;

		for (auto& check : checks)
		{
			if (!check)
				++checks_failed;
			else
				++checks_succeeded;
		}

		print(bold, red, " failed: (", detail, ") ", reset);
		print(red, "failed: ", bold, checks_failed, reset);
		print(green, ", succeeded: ", bold, checks_succeeded, reset, '\n');

		for (auto& check : checks)
		{
			if (!check)
				print(bold, red, "check failed: ", reset, check.message, '\n');
		}
	}

private:
	void test_start(const char* name)
	{
		print(bold, '[', ++count, '/', total, ']', ' ', reset);
		print("test \"", bold, name, reset, '"');
	}

private:
	int total;
	int count     = 0;
	int succeeded = 0;
	int failed    = 0;

	const char* filename;
};

class report_junit : public report {
public:
	void begin_suite(const char* name, int test_count) override
	{
		println("<testsuite tests=\"", test_count, "\" name=\"", name, "\">");
	}

	void end_suite()
	{
		println("</testsuite>");

	}

	void test_success(const char* name, const std::vector<check_report>& checks) override
	{
		println("<testcase name=\"", name, "\"/>");
	}

	void test_failure(const char* name, const std::vector<check_report>& checks, const char* detail) override
	{
		println("<testcase name=\"", name, "\">");
		for (auto& check : checks)
		{
			if (check)
				continue;
			println("<failure type=\"check_failed\">" + check.message + "\"</failure>");
		}
		println("</testcase>");
	}
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

		_report->begin_suite(filename, tests.size());

		for (test& test_case : tests)
			run_test(test_case);

		_report->end_suite();

		return failed;
	}

	bool check_fail(std::string const& msg)
	{
		cur->checks.push_back(check_report{false, msg});
		return false;
	}

	bool check_succeed(std::string const& msg)
	{
		cur->checks.push_back(check_report{true, msg});
		return true;
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
		for (const auto& check : cur->checks)
			if (!check)
				throw test_failed{};
		cur->st = st;
	}

	inline void test_failure();
	inline void test_success();

	void add_test(test&& tst)
	{
		tests.push_back(std::move(tst));
	}

private:
	test* cur;
	report_junit rengine;
	report* _report = &rengine;
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

	_report->test_failure( cur->name, cur->checks, stage_name[size_t(cur->st)] );
}

void context::test_success()
{
	_report->test_success( cur->name, cur->checks );
}

void context::run_test(test& tst)
{
	using namespace std::string_literals;

	cur = &tst;

	try {
		enter(stage::start);
		cur->func();
		enter(stage::end);
		return test_success();
	}
	catch (test_failed& ex)
	{
		test_failure();
	}
	catch (std::exception& e)
	{
		cur->checks.push_back(check_report{ false, "unhandled exception: "s + e.what() });
		test_failure();
	}
	catch (...)
	{
		cur->checks.push_back(check_report{ false, "caught unknown exception" });
		test_failure();
	}
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
bool check(Evaluator eval, Args&&... args)
{
	return eval(std::forward<Args>(args)...) ?
		file_context.check_succeed(eval.msg()) :
		file_context.check_fail(eval.msg());
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
		return vargs + ": "s + got + " == "s + expected;
	}

	char const* vargs;
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
		return vargs + " values: "s + values;
	}

	char const* vargs;
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

template<typename Ex>
struct _catch {
	template <typename F>
	bool operator()(F func)
	{
		using namespace std::string_literals;
		try {
			func();
		} catch(Ex&) {
			return true;
		} catch(std::exception& e) {
			auto name = type_name( typeid(e) );
			auto what = " - \""s + e.what() + '"';
			_msg = "caught wrong exception: " + name + what;
			return false;
		} catch(...) {
			_msg = "caught wrong exception";
			return false;
		}
		_msg = "didn't catch any exception";
		return false;
	}

	std::string msg() { return _msg; }
	std::string _msg;
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

#include <aw/meta/pp/macro.h>
#define TestEqual(...) \
aw::test::check(aw::test::equal{#__VA_ARGS__}, __VA_ARGS__)
#define TestEqualV(...) \
aw::test::check(aw::test::equal_v{#__VA_ARGS__}, __VA_ARGS__)
#define TestAssert(...) \
aw::test::check(aw::test::_assert{"assert: " #__VA_ARGS__}, (__VA_ARGS__))
#define TestFail(msg) \
aw::test::file_context.check_fail(msg)
#define TestCatch(exception, ...) \
aw::test::check(aw::test::_catch<exception>{}, [&] {__VA_ARGS__;} )

#endif//aw_test_test_h
