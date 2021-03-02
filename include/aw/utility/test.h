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
#include <aw/test/test_case.h>
#include <aw/test/test_report.h>
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
 * deserve a separate directory.
 */

int main(int,char**);

namespace aw {
namespace test {

struct test_failed : std::exception {};


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

	inline static int run(report* _report);
};



struct context {
	context(char const* filename)
		: filename(filename)
	{
		registry::add(*this);
	}

	test_case& current() { return *cur; }
	char const* const filename;

	int run(report* _report)
	{
		install_handler();

		// TODO: deprecate report, save data in a structured way
		_report->begin_suite(filename, tests.size());

		for (test_case& test : tests)
			run_test_case(test, _report);

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

	inline void run_test_case(test_case& tst, report* _report);

	void enter(stage st)
	{
		for (const auto& check : cur->checks)
			if (!check)
				throw test_failed{};
		cur->st = st;
	}

	inline void test_failure(report* _report);
	inline void test_success(report* _report);

	void add_test(test_case&& tst)
	{
		tests.push_back(std::move(tst));
	}

private:
	test_case* cur;
	std::vector<test_case> tests;
	unsigned failed = 0;
};

int registry::run(report* reporter)
{
	auto& vec = static_object<_ctxs>::instance().ctxs;

	int res = 0;
	for (auto& ctx : vec)
		res += ctx->run(reporter);

	return res > 0xFF ? 0xFF : res;
}

void context::test_failure(report* _report)
{
	++failed;

	_report->test_failure( cur->name, cur->checks, stage_name[size_t(cur->st)] );
}

void context::test_success(report* _report)
{
	_report->test_success( cur->name, cur->checks );
}

void context::run_test_case(test_case& test, report* _report)
{
	using namespace std::string_literals;

	cur = &test;

	try {
		enter(stage::start);
		cur->func();
		enter(stage::end);
		return test_success(_report);
	}
	catch (test_failed& ex)
	{
		test_failure(_report);
	}
	catch (std::exception& e)
	{
		cur->checks.push_back(check_report{ false, "unhandled exception: "s + e.what() });
		test_failure(_report);
	}
	catch (...)
	{
		cur->checks.push_back(check_report{ false, "caught unknown exception" });
		test_failure(_report);
	}
}

namespace {
extern context file_context;
}

void context::segvhandler(int signum)
{
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
	//file_context.test_failure();
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
public:
	register_test(const char* test_name, test_case::test_function* test_func)
	{
		add_test(aw::test::test_case{test_name, test_func});
	}

protected:
	void add_test(test_case&& tst)
	{
		file_context.add_test(std::move(tst));
	}
};

bool setup()          { context_block::enter(stage::setup); return true; }
bool preconditions()  { context_block::enter(stage::preconditions); return true; }
bool checks()         { context_block::enter(stage::checks); return true; }
bool postconditions() { context_block::enter(stage::postconditions); return true; }
} // namespace

template<typename Evaluator, typename... Args>
bool check(Evaluator eval, Args&&... args)
{
	return eval(std::forward<Args>(args)...) ?
		file_context.check_succeed(eval.msg()) :
		file_context.check_fail(eval.msg());
}
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

#define TestFile(name) namespace aw::test { namespace { context file_context{name}; } }
#define Test(name)     \
	void run_test_##name(); \
	aw::test::register_test add_test_##name{#name, run_test_##name}; \
	void run_test_##name()
#define Setup          if (aw::test::setup())
#define Preconditions  if (aw::test::preconditions())
#define Checks         if (aw::test::checks())
#define Postconditions if (aw::test::postconditions())

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
