/*
 * Copyright (C) 2016-2022  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_report_h
#define aw_test_report_h

#include <aw/test/test_case.h>

namespace aw::test {

class report {
public:
	virtual void begin_suite(const char* name, int test_count) = 0;
	virtual void end_suite() = 0;

	virtual void test_success(const char* name, const std::vector<check_report>& checks) = 0;
	virtual void test_failure(const char* name, const std::vector<check_report>& checks, const char* detail) = 0;
};

} // namespace aw::test

#endif // aw_test_report_h
