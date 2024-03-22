#include <aw/io/process.h>
#include <aw/io/filesystem.h>

#include <aw/utility/on_scope_exit.h>
#include <aw/utility/string/trim.h>

#include <aw/test/test.h>

#include <fstream>

TestFile("Test");

namespace aw {
Test(process_basic_test) {
	using namespace std::string_literals;

	auto cd_guard = on_scope_exit([cd = fs::current_path()] { fs::current_path(cd); });
	fs::current_path(_context.exe_dir);

	auto path = io::executable_name("dump_args"s);

	auto result = io::run(path, { "a", "b", "c" });

	TestAssert(result == io::wait_status::finished);

	std::vector<std::string> args_expect{ { path, "a", "b", "c" } };
	std::vector<std::string> args;
	{
		std::ifstream fs("argv.txt");
		std::string str;
		while (std::getline(fs, str)) {
			const auto pred = [] (char c) { return std::isspace(c); };
			args.push_back(string::rtrimmed(str, pred));
		}
	}

	TestEqual(args, args_expect);
}

} // namespace aw
