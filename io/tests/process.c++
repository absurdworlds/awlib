#include <aw/io/process.h>
#include <aw/io/filesystem.h>

#include <aw/utility/on_scope_exit.h>
#include <aw/utility/string/trim_if.h>
#include <aw/string/format.h>

#include <aw/test/test.h>

#include <chrono>
#include <fstream>

#include <aw/config.h>

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#endif

TestFile("Test");

namespace aw {

static auto read_all(std::string filename, char delim = '\n') -> std::vector<std::string>
{
	std::vector<std::string> args;
	std::ifstream fs(filename);
	std::string str;
	while (std::getline(fs, str, delim)) {
		const auto pred = [] (char c) { return std::isspace(c); };
		args.push_back(string::rtrimmed_if(str, pred));
	}
	return args;
}

Test(process_basic_test) {
	using namespace std::string_literals;

	auto cd_guard = on_scope_exit([cd = fs::current_path()] { fs::current_path(cd); });
	fs::current_path(_context.exe_dir);

	auto path = io::executable_name("dump_args"s);

	std::vector<std::string> in_args = { "a", "b", "c" };
	auto result = io::run(path, in_args);

	TestAssert(result == io::wait_status::finished);

	std::vector<std::string> args_expect{ { path, "a", "b", "c" } };
	std::vector<std::string> args = read_all("argv.txt");

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

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
/*!
 * Check whether \a pid is still waiting to be reaped.
 */
static bool awaits_reaping(io::process_handle pid)
{
	int status = 0;
	errno = 0;
	if (waitpid( pid_t(pid), &status, WNOHANG ) >= 0)
		return true;
	return errno != ECHILD;
}

/*!
 * A signal arriving during wait() must not interrupt the wait
 */
Test(wait_survives_a_signal) {
	using namespace std::string_literals;
	using namespace std::chrono;

	auto cd_guard = on_scope_exit([cd = fs::current_path()] { fs::current_path(cd); });
	fs::current_path(_context.exe_dir);

	constexpr auto child_lifetime = 300ms;
	constexpr auto signal_after   = 50ms;

	// disable SA_RESTART
	struct sigaction interrupt = {};
	interrupt.sa_handler = [] (int) {};
	interrupt.sa_flags   = 0;

	struct sigaction previous = {};
	sigaction(SIGALRM, &interrupt, &previous);

	auto signal_guard = on_scope_exit([&previous] {
		itimerval off = {};
		setitimer(ITIMER_REAL, &off, nullptr);
		sigaction(SIGALRM, &previous, nullptr);
	});

	auto path = io::executable_name("dump_args"s);
	std::vector<std::string> args = {
		format("--sleep-ms={}", child_lifetime.count())
	};

	std::error_code ec;
	auto handle = io::spawn(path, args, ec);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	itimerval timer = {};
	timer.it_value.tv_usec = duration_cast<microseconds>(signal_after).count();
	setitimer(ITIMER_REAL, &timer, nullptr);

	auto started = steady_clock::now();
	auto status  = io::wait(handle, ec);
	auto waited  = steady_clock::now() - started;

	Checks {
		TestAssert( status == io::wait_status::finished );

		// the wait ran to the child's exit, not to the signal
		TestAssert( waited >= child_lifetime );

		// nothing is left to reap
		TestAssert( !awaits_reaping(handle) );
	}
}
#endif

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
