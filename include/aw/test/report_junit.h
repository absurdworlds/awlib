/*
 * Copyright (C) 2016-2020 Hedede <haddayn@gmail.com>
 * License LGPLv3 or later: <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_report_junit_h
#define aw_test_report_junit_h

#include <aw/test/test_case.h>
#include <aw/test/print.h>

namespace aw::test {
class report_junit : public report {
public:
	void begin_suite(const char* name, int test_count) override
	{
		test_cases.clear();
		succeeded = 0;
		failed    = 0;
		this->name = name;
		this->total = test_count;
	}

	void end_suite()
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
#endif aw_test_report_juni_h
