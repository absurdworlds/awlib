/*
 * Copyright (C) 2016-2022  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_registry_h
#define aw_test_registry_h

#include <iostream>
#include <vector>
#include <csignal>

#include <aw/config.h>
#include <aw/utility/static_object.h>
#include <aw/test/report.h>

int main(int,char**);

namespace aw::test {

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

struct test_failed : std::exception {};

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

	void enter(stage st)
	{
		for (const auto& check : cur->checks)
			if (!check)
				throw test_failed{};
		cur->st = st;
	}

	void add_test(test_case&& tst)
	{
		tests.push_back(std::move(tst));
	}

private:
	inline static void segvhandler(int signum);

	void install_handler()
	{
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
		signal(SIGSEGV, segvhandler);
#endif
	}

	inline void run_test_case(test_case& tst, report* _report);


	inline void test_failure(report* _report);
	inline void test_success(report* _report);

private:
	test_case* cur;
	std::vector<test_case> tests;
	unsigned failed = 0;
};

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

} // namespace aw::test

#endif // aw_test_registry_h
