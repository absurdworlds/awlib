/*
 * Copyright (C) 2016-2020  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_test_case_h
#define aw_test_test_case_h
#include <vector>
#include <string>

#include "test_context.h"

namespace aw::test {
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

struct test_case {
	using test_function = void(test_context exe_dir);
	test_case(char const* name, test_function* func)
		: name{name}, func{func}
	{ }

	char const* const name;

private:
	friend struct context;

	test_function* const func;

	stage st = stage::start;

	std::vector<check_report> checks;
};
} // namespace aw::test
#endif//aw_test_test_case_h
