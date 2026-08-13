#include <aw/utility/argv_parser.h>
#include <aw/string/parse.h>

#include <fstream>
#include <chrono>
#include <string>
#include <thread>

struct arguments {
	//! `--sleep-ms=N` keeps the process alive for N milliseconds before exiting
	unsigned sleep_ms = 0;
	//! `--exit=N` sets the exit code of the process
	unsigned code = 0;
};

static arguments parse_arguments(char** argv)
{
	using token = aw::utils::argument_token;

	arguments args;
	aw::utils::argv_parser parser{ argv };

	while (auto arg = parser.parse_argument()) {
		if (arg->type != token::option)
			continue;

		if (arg->name == "sleep-ms")
			args.sleep_ms = aw::string::parse(arg->value, 0u);
		else if (arg->name == "exit")
			args.code = aw::string::parse(arg->value, 0u);
	}

	return args;
}

// simple test executable to test process api wrappers
int main(int, char** argv)
{
	const auto args = parse_arguments(argv);

	{
		// TODO: temp_file
		std::ofstream f("argv.txt");
		while (auto str = *argv++)
			f << str << std::endl;
	}

	if (args.sleep_ms > 0)
		std::this_thread::sleep_for( std::chrono::milliseconds(args.sleep_ms) );

	return int(args.code);
}
