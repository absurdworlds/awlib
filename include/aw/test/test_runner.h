#include <aw/utility/test.h>
#include <aw/utility/argv_parser.h>

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
