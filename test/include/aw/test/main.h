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

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace aw::test {

struct test_config {
	bool use_junit   = false;
	bool no_exitcode = false;
	//! Where to write the report; empty means standard output
	std::string output_file;
};

test_config parse_parameters(char** begin, char** end)
{
	using namespace std::string_view_literals;

	test_config config;

	if (auto* format = std::getenv("AW_TEST_OUTPUT_FORMAT"))
		config.use_junit = (std::string_view(format) == "junit"sv);
	if (auto* file = std::getenv("AW_TEST_OUTPUT_FILE"))
		config.output_file = file;

	// command line overrides the env
	auto param_output_format = "--output-format="sv;
	auto param_output_file   = "--output-file="sv;
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

		if (param.find(param_output_file) == 0)
		{
			param.remove_prefix(param_output_file.size());
			config.output_file = param;
		}

		if (param == param_no_exitcode)
		{
			config.no_exitcode = true;
		}

	}

	return config;
}

int registry::run(std::string_view exe_dir, report* reporter)
{
	auto& vec = static_object<_ctxs>::instance().ctxs;

	reporter->begin_tests();

	int total = 0;
	for (auto& ctx : vec)
		total += ctx->test_count();

	int res = 0;
	for (auto& ctx : vec)
		res += ctx->run(exe_dir, reporter);

	reporter->end_tests(total, res);

	return res > 0xFF ? 0xFF : res;
}

} // namespace aw::test

int main(int n_param, char** parameters)
{
	using namespace aw::test;

	auto dir_name = [] (std::string_view s) {
		return std::filesystem::path(s).parent_path().string();
	};

	auto config = parse_parameters(parameters, parameters + n_param);

	std::ofstream file;
	if (!config.output_file.empty())
	{
		file.open(config.output_file);
		if (!file)
		{
			std::cerr << "cannot open " << config.output_file << " for writing\n";
			return 1;
		}
	}

	std::ostream& file_out = file.is_open() ? static_cast<std::ostream&>(file) : std::cout;

	report_classic classic{ config.use_junit ? std::cout : file_out };
	report_junit   junit{ file_out };

	/*
	 * When the report is written to a file, the console still gets the
	 * human-readable one, so that `ctest --output-on-failure` keeps saying
	 * which checks failed.
	 */
	report_tee tee{ &junit, &classic };

	report* _report = !config.use_junit ? (report*)&classic
	                : file.is_open()    ? (report*)&tee
	                                    : (report*)&junit;

	int fail_count = aw::test::registry::run(dir_name(parameters[0]), _report);

	return config.no_exitcode ? 0 : fail_count;
}

#endif // aw_test_main_h
