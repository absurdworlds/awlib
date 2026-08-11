#include <aw/io/process.h>
#include <aw/io/filesystem.h>

#include <aw/utility/on_scope_exit.h>
#include <aw/utility/string/trim_if.h>

#include <aw/test/test.h>

#include <fstream>

#include <aw/config.h>

TestFile("Test");

namespace aw {
Test(process_basic_test) {
	using namespace std::string_literals;

	auto cd_guard = on_scope_exit([cd = fs::current_path()] { fs::current_path(cd); });
	fs::current_path(_context.exe_dir);

	auto path = io::executable_name("dump_args"s);

	std::vector<std::string> in_args = { "a", "b", "c" };
	auto result = io::run(path, in_args);

	TestAssert(result == io::wait_status::finished);

	std::vector<std::string> args_expect{ { path, "a", "b", "c" } };
	std::vector<std::string> args;
	{
		std::ifstream fs("argv.txt");
		std::string str;
		while (std::getline(fs, str)) {
			const auto pred = [] (char c) { return std::isspace(c); };
			args.push_back(string::rtrimmed_if(str, pred));
		}
	}

	TestEqual(args, args_expect);
}

Test(spawn_without_arguments_reports_error) {
	std::error_code ec;

	Checks {
		// reject empty argv
		aw::array_view<const char*> argv;

		auto handle = io::spawn(argv, ec);
		TestAssert( handle == io::invalid_process_handle );
		TestAssert( ec == std::errc::invalid_argument );
	}

	Checks {
		// reject argv with only null-terminator in it
		const char* argv[] = { nullptr };

		auto handle = io::spawn(argv, ec);
		TestAssert( handle == io::invalid_process_handle );
		TestAssert( ec == std::errc::invalid_argument );
	}
}

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
Test(win32_spawn_does_not_leak_thread_handle) {
	using namespace std::string_literals;

	auto cd_guard = on_scope_exit([cd = fs::current_path()] { fs::current_path(cd); });
	fs::current_path(_context.exe_dir);

	auto path = io::executable_name("dump_args"s);
	std::vector<std::string> args = { "x" };

	constexpr int iterations = 25;

	auto before = io::win32::current_process::handle_count();

	for (int i = 0; i < iterations; ++i)
		io::run(path, args);

	auto after = io::win32::current_process::handle_count();

	Checks {
		TestLess(after, before + iterations);
	}
}
#endif

} // namespace aw
