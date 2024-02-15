/*
 * Copyright (C) 2016-2022  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_report_impl_h
#define aw_test_report_impl_h

#include <aw/test/report.h>
#include <aw/test/print.h>

namespace aw::test {

class report_classic : public report {
public:
	void begin_tests() override
	{
		println(bold, "[***] begin tests");
	}
	void end_tests(int total, int failed) override
	{
		println(bold, "[***] end tests: ", total - failed, '/', total, " succeeded");
	}

	void begin_suite(const char* name, int test_count) override
	{
		filename  = name;
		total     = test_count;
		count     = 0;
		succeeded = 0;
		failed    = 0;

		println(bold, '[', filename, ']', ' ', reset, "running tests");
	}

	void end_suite() override
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
	void begin_tests() override {}
	void end_tests(int total, int failed) override {}

	void begin_suite(const char* name, int test_count) override
	{
		test_cases.clear();
		succeeded = 0;
		failed    = 0;
		this->name = name;
		this->total = test_count;
	}

	void end_suite() override
	{
		int skipped = total - succeeded - failed;
		print("<testsuite name=\"", name, "\" tests=\"", total, "\" errors=\"0\" ");
		println("failures=\"", failed, "\" skipped=\"", skipped, "\">");
		for (const auto& test_case : test_cases)
		{
			if (test_case.success)
			{
				println("<testcase name=\"", test_case.name, "\" time=\"0\"/>");
			}
			else
			{
				println("<testcase name=\"", test_case.name, "\" time=\"0\">");
				for (auto& check : test_case.checks)
				{
					if (check)
						continue;
					println("<failure type=\"check_failed\">" + check.message + "\"</failure>");
				}
				println("</testcase>");
			}
		}
		println("</testsuite>");

	}

	void test_success(const char* name, const std::vector<check_report>& checks) override
	{
		++succeeded;
		test_cases.push_back(test_case{true, name, checks});
	}

	void test_failure(const char* name, const std::vector<check_report>& checks, const char* detail) override
	{
		++failed;
		test_cases.push_back(test_case{false, name, checks});
	}

private:
	struct test_case {
		bool success;
		std::string name;
		std::vector<check_report> checks;
	};
	std::vector<test_case> test_cases;

	std::string name;
	int total;
	int succeeded = 0;
	int failed    = 0;

};
} // namespace aw::test

#endif // aw_test_report_impl_h
