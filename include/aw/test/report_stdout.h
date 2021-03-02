/*
 * Copyright (C) 2016-2020 Hedede <haddayn@gmail.com>
 * License LGPLv3 or later: <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_report_stdout_h
#define aw_test_report_stdout_h

#include <aw/test/test_case.h>
#include <aw/test/print.h>
#include <aw/config.h>

namespace aw::test {

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


class report_classic : public report {
public:
	void begin_suite(const char* name, int test_count) override
	{
		filename  = name;
		total     = test_count;
		count     = 0;
		succeeded = 0;
		failed    = 0;

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

} // namespace aw::test

#endif aw_test_report_stdout_h
