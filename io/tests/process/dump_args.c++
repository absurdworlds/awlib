#include <fstream>
#include <charconv>
#include <chrono>
#include <string_view>
#include <thread>

// TODO: use argv_parser

//! `--sleep-ms=N` keeps the process alive for N milliseconds before exiting
static unsigned sleep_argument(char** argv)
{
	constexpr std::string_view option = "--sleep-ms=";

	for (auto arg = argv; *arg; ++arg) {
		const std::string_view str{*arg};
		if (!str.starts_with(option))
			continue;

		const auto num = str.substr(option.size());
		unsigned ms = 0;
		std::from_chars(num.data(), num.data() + num.size(), ms);
		return ms;
	}

	return 0;
}

// simple test executable to test process api wrappers
int main(int, char** argv)
{
	const auto sleep_ms = sleep_argument(argv);

	{
		// TODO: temp_file
		std::ofstream f("argv.txt");
		while (auto str = *argv++)
			f << str << std::endl;
	}

	if (sleep_ms > 0)
		std::this_thread::sleep_for( std::chrono::milliseconds(sleep_ms) );
}
