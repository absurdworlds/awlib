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
#include <aw/test/registry.h>
#include <aw/test/report.h>
#include <aw/test/print.h>
#include <aw/test/segv_handler.h>
#include <aw/platform/demangle.h>
#include <aw/utility/to_string.h>
#include <aw/types/strip.h>
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <cstdio>
#endif

namespace aw {
namespace test {

namespace {
extern context file_context;
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
		std::vector<std::remove_cvref_t<T>> tmp = {arg, args...};
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
	const aw::test::register_test add_test_##name{#name, run_test_##name}; \
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
