#include <aw/utility/argv_parser.h>
#include <aw/string/parse.h>
#include <aw/io/native_file.h>

#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

struct arguments {
	//! `--sleep-ms=N` keeps the process alive for N milliseconds before exiting
	unsigned sleep_ms = 0;
	//! `--exit=N` sets the exit code of the process
	unsigned code = 0;
	//! `--cat` copies stdin to stdout
	bool cat = false;
	//! `--write-to=N` writes a message to the inherited descriptor N
	unsigned long long write_to = 0;
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
		else if (arg->name == "cat")
			args.cat = true;
		else if (arg->name == "write-to")
			args.write_to = aw::string::parse(arg->value, 0ull);
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

	if (args.cat)
		std::cout << std::cin.rdbuf() << std::flush;

	if (args.write_to != 0) {
		// a descriptor on POSIX, a handle value on Windows
		const auto fd = aw::io::file_descriptor(args.write_to);
		const std::string message = "inherited";
		std::error_code ec;
		aw::io::native::write(fd, message.data(), message.size(), ec);
		if (ec)
			return 3;
	}

	if (args.sleep_ms > 0)
		std::this_thread::sleep_for( std::chrono::milliseconds(args.sleep_ms) );

	return int(args.code);
}
