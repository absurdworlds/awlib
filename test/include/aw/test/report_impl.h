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

#include <string>
#include <string_view>
#include <vector>

namespace aw::test {

class report_classic : public report {
public:
	using report::report;

	void begin_tests() override
	{
		println(out, bold, "[***] begin tests");
	}

	void end_tests(int total, int failed) override
	{
		println(out, bold, "[***] end tests: ", total - failed, '/', total, " succeeded");
	}

	void begin_suite(const char* name, int test_count) override
	{
		filename  = name;
		total     = test_count;
		count     = 0;
		succeeded = 0;
		failed    = 0;

		println(out, bold, '[', filename, ']', ' ', reset, "running tests");
	}

	void end_suite() override
	{
		print(out, bold, '[', filename, ']', ' ', reset);
		print(out, "tests done, failed: ");
		print(out, bold, (failed > 0 ? red : white), failed, reset);
		print(out, ", succeeded: ");
		print(out, bold, (succeeded > 0 ? green : white), succeeded, reset);
		print(out, reset, '\n');

	}

	void test_success(const char* name, const std::vector<check_report>& checks) override
	{
		++succeeded;

		test_start(name);

		println(out, bold, green, " succeeded, checks: ", checks.size(), reset);
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

		print(out, bold, red, " failed: (", detail, ") ", reset);
		print(out, red, "failed: ", bold, checks_failed, reset);
		print(out, green, ", succeeded: ", bold, checks_succeeded, reset, '\n');

		for (auto& check : checks)
		{
			if (!check)
				print(out, bold, red, "check failed: ", reset, check.message, '\n');
		}
	}

private:
	void test_start(const char* name)
	{
		print(out, bold, '[', ++count, '/', total, ']', ' ', reset);
		print(out, "test \"", bold, name, reset, '"');
	}

private:
	int total;
	int count     = 0;
	int succeeded = 0;
	int failed    = 0;

	const char* filename;
};

/*!
 * Hands everything it is told to several reports at once, so that one run
 * can be written out in more than one form.
 */
class report_tee : public report {
public:
	report_tee(std::initializer_list<report*> list)
		: report(std::cout), reports(list)
	{}

	void begin_tests() override
	{
		for (auto* r : reports) r->begin_tests();
	}

	void end_tests(int total, int failed) override
	{
		for (auto* r : reports) r->end_tests(total, failed);
	}

	void begin_suite(const char* name, int test_count) override
	{
		for (auto* r : reports) r->begin_suite(name, test_count);
	}

	void end_suite() override
	{
		for (auto* r : reports) r->end_suite();
	}

	void test_success(const char* name, const std::vector<check_report>& checks) override
	{
		for (auto* r : reports) r->test_success(name, checks);
	}

	void test_failure(const char* name, const std::vector<check_report>& checks, const char* detail) override
	{
		for (auto* r : reports) r->test_failure(name, checks, detail);
	}

private:
	std::vector<report*> reports;
};

//! Replace the characters which may not appear literally in XML
inline std::string xml_escape(std::string_view in)
{
	std::string out;
	for (char c : in)
	{
		switch (c)
		{
		case '&': out += "&amp;";  break;
		case '<': out += "&lt;";   break;
		case '>': out += "&gt;";   break;
		case '"': out += "&quot;"; break;
		default:  out += c;
		}
	}
	return out;
}

class report_junit : public report {
public:
	using report::report;

	// the whole run is one document, so the root element wraps every suite
	void begin_tests() override
	{
		println(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		println(out, "<testsuites>");
	}

	void end_tests(int total, int failed) override
	{
		println(out, "</testsuites>");
	}

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
		print(out, "<testsuite name=\"", xml_escape(name), "\" tests=\"", total, "\" errors=\"0\" ");
		println(out, "failures=\"", failed, "\" skipped=\"", skipped, "\">");
		for (const auto& test_case : test_cases)
		{
			if (test_case.success)
			{
				println(out, "<testcase name=\"", xml_escape(test_case.name), "\" time=\"0\"/>");
			}
			else
			{
				println(out, "<testcase name=\"", xml_escape(test_case.name), "\" time=\"0\">");
				for (auto& check : test_case.checks)
				{
					if (check)
						continue;
					println(out, "<failure type=\"check_failed\">", xml_escape(check.message), "</failure>");
				}
				println(out, "</testcase>");
			}
		}
		println(out, "</testsuite>");

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
