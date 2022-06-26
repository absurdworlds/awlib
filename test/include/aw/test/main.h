/*
 * Copyright (C) 2016-2022  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_main_h
#define aw_test_main_h

#include <aw/test/report_impl.h>
#include <aw/test/registry.h>
#include <aw/utility/argv_parser.h>

namespace aw::test {

struct test_config {
	bool use_junit   = false;
	bool no_exitcode = false;
};
test_config parse_parameters(char** begin, char** end)
{
	using namespace std::string_view_literals;

	test_config config;

	auto param_output_format = "--output-format="sv;
	auto param_no_exitcode   = "--no-exitcode"sv;

	for ( auto iter = begin; iter < end; ++iter )
	{
		std::string_view param = *iter;
		if (param.find(param_output_format) == 0)
		{
			param.remove_prefix(param_output_format.size());
			if (param == "junit"sv)
				config.use_junit = true;
		}

		if (param == param_no_exitcode)
		{
			config.no_exitcode = true;
		}

	}

	return config;
}

int registry::run(report* reporter)
{
	auto& vec = static_object<_ctxs>::instance().ctxs;

	int res = 0;
	for (auto& ctx : vec)
		res += ctx->run(reporter);

	return res > 0xFF ? 0xFF : res;
}

} // namespace aw::test

int main(int n_param, char** parameters)
{
	using namespace aw::test;

	auto config = parse_parameters(parameters, parameters + n_param);

	report_classic classic;
	report_junit   junit;

	report* _report = config.use_junit ? (report*)&junit : (report*)&classic;

       	int fail_count = aw::test::registry::run(_report);

	return config.no_exitcode ? 0 : fail_count;
}

#endif // aw_test_main_h
