#include <aw/io/process.h>
#include <aw/io/filesystem.h>

#include <aw/utility/on_scope_exit.h>
#include <aw/utility/string/trim_if.h>
#include <aw/string/format.h>

#include <aw/test/test.h>

#include <chrono>
#include <csignal>
#include <type_traits>
#include <fstream>

#include <aw/config.h>

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#endif

TestFile("io::process");

namespace aw {

static auto read_all_lines(std::string filename, char delim = '\n') -> std::vector<std::string>
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

/*!
 * Shared helper for the process tests
 */
struct process_fixture {
	explicit process_fixture(test::test_context context)
		: previous_path{ fs::current_path() }
	{
		fs::current_path(context.exe_dir);
	}

	~process_fixture()
	{
		fs::current_path(previous_path);
	}

	process_fixture(process_fixture const&) = delete;
	process_fixture& operator=(process_fixture const&) = delete;

	//! Spawn the helper process
	//! \param lifetime ms to keep it alive for
	auto spawn(std::chrono::milliseconds lifetime = {})
	{
		std::vector<std::string> args;
		if (lifetime > lifetime.zero())
			args.push_back( format("--sleep-ms={}", lifetime.count()) );

		return io::spawn(helper, args, ec);
	}

	//! Populate \a ec with an error
	void fail()
	{
		io::run(missing, no_args, ec);
	}

	fs::path previous_path;

	std::vector<std::string> no_args;

	std::string helper  = io::executable_name( std::string("dump_args") );
	std::string missing = io::executable_name( std::string("no_such_executable") );

	std::error_code ec;
};

Test(process_basic_test) {
	process_fixture test{_context};

	std::vector<std::string> in_args = { "a", "b", "c" };
	auto result = io::run(test.helper, in_args);

	TestAssert(result == io::wait_status::finished);

	std::vector<std::string> args_expect{ { test.helper, "a", "b", "c" } };
	std::vector<std::string> args = read_all_lines("argv.txt");

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

Test(terminate_stops_the_child) {
	using namespace std::chrono;

	process_fixture test{_context};

	// long enough that it cannot have finished on its own
	constexpr auto child_lifetime = 30s;

	auto handle = test.spawn(child_lifetime);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	auto started = steady_clock::now();

	Checks {
		TestAssert( io::terminate(handle, test.ec) == 0 );
		TestAssert( !test.ec );
	}

	Checks {
		TestAssert( io::wait(handle, test.ec) == io::wait_status::finished );
		TestAssert( steady_clock::now() - started < child_lifetime );
	}
}

/*!
 * A wait must return at the deadline rather than waiting for the child
 */
Test(wait_gives_up_at_the_deadline) {
	using namespace std::chrono;

	process_fixture test{_context};

	constexpr auto child_lifetime = 500ms;
	constexpr auto give_up_after  = 50ms;

	auto handle = test.spawn(child_lifetime);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	auto started = steady_clock::now();
	auto status  = io::wait(handle, test.ec, give_up_after);
	auto waited  = duration_cast<milliseconds>( steady_clock::now() - started );

	/*
	 * WaitForSingleObject expires on a system timer tick,
	 * historically ~15.6ms by default
	 * TODO: revisit this, and maybe strengthen guarantees to match posix
	 */
	constexpr auto timer_slack = 16ms;

	Checks {
		TestAssert( status == io::wait_status::timeout );
		TestLess( (give_up_after - timer_slack).count(), waited.count() );
		TestLess( waited.count(), child_lifetime.count() );
	}

	// the child outlived the wait, so it is still there to collect
	Checks {
		TestAssert( io::wait(handle, test.ec) == io::wait_status::finished );
	}
}

/*!
 * A child that beats the deadline is reported as finished, not timed out
 */
Test(wait_with_a_deadline_reports_child_as_finished) {
	using namespace std::chrono;

	process_fixture test{_context};

	constexpr auto child_lifetime = 50ms;
	constexpr auto give_up_after  = 1s;

	auto handle = test.spawn(child_lifetime);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	auto started = steady_clock::now();
	auto status  = io::wait(handle, test.ec, give_up_after);
	auto waited  = steady_clock::now() - started;

	Checks {
		TestAssert( status == io::wait_status::finished );
		TestAssert( waited < give_up_after );
	}
}

/*!
 * \a ec must be cleared on success, not left untouched
 */
Test(success_clears_the_error_code) {
	process_fixture test{_context};

	Preconditions {
		test.fail();
		TestAssert( bool(test.ec) );
	}

	Checks {
		auto handle = test.spawn();
		TestAssert( handle != io::invalid_process_handle );
		TestAssert( !test.ec ); // "spawn clears ec"

		io::wait(handle, test.ec);
	}

	Checks {
		auto handle = test.spawn();
		test.fail();
		TestAssert( bool(test.ec) );

		TestAssert( io::wait(handle, test.ec) == io::wait_status::finished );
		TestAssert( !test.ec ); // "wait clears ec"
	}
}

/*!
 * kill() has to clear the error code on success as well
 */
Test(kill_clears_the_error_code) {
	using namespace std::chrono;

	process_fixture test{_context};

	auto handle = test.spawn(300ms);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );

		test.fail();
		TestAssert( bool(test.ec) );
	}

	Checks {
		TestAssert( io::kill(handle, SIGTERM, test.ec) == 0 );
		TestAssert( !test.ec );
	}

	io::wait(handle, test.ec);
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
 * Signal helper. Replaces the signal handler for SIGALRM and raises
 * the signal after the specified delay.
 */
struct alarm_after {
	/*!
	 * Installs a SIGALRM handler without SA_RESTART and
	 * raises the alarm after \a delay
	 */
	explicit alarm_after(std::chrono::microseconds delay)
	{
		struct sigaction interrupt = {};
		interrupt.sa_handler = [] (int) {};
		interrupt.sa_flags   = 0;

		sigaction(SIGALRM, &interrupt, &previous);

		itimerval timer = {};
		timer.it_value.tv_usec = delay.count();
		setitimer(ITIMER_REAL, &timer, nullptr);
	}

	//! Stops the alarm and restores the old signal handler
	~alarm_after()
	{
		itimerval off = {};
		setitimer(ITIMER_REAL, &off, nullptr);
		sigaction(SIGALRM, &previous, nullptr);
	}

	alarm_after(alarm_after const&) = delete;
	alarm_after& operator=(alarm_after const&) = delete;

	struct sigaction previous = {};
};

/*!
 * A signal arriving during wait() must not interrupt the wait
 */
Test(wait_survives_a_signal) {
	using namespace std::chrono;

	process_fixture test{_context};

	constexpr auto child_lifetime = 300ms;
	constexpr auto signal_after   = 50ms;

	auto handle = test.spawn(child_lifetime);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	alarm_after alarm{ duration_cast<microseconds>(signal_after) };

	auto started = steady_clock::now();
	auto status  = io::wait(handle, test.ec);
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
static_assert( std::is_convertible_v<io::win32::process_holder const&,
                                     io::win32::process_handle> );

Test(win32_spawn_does_not_leak_thread_handle) {
	process_fixture test{_context};

	std::vector<std::string> args = { "x" };

	constexpr int iterations = 25;

	auto before = io::win32::current_process::handle_count();

	for (int i = 0; i < iterations; ++i)
		io::run(test.helper, args);

	auto after = io::win32::current_process::handle_count();

	Checks {
		TestLess(after, before + iterations);
	}
}

/*!
 * A handle holder assigned onto itself still refers to its process
 */
Test(win32_self_move_assignment_keeps_the_handle) {
	using namespace std::chrono;

	process_fixture test{_context};

	auto handle = test.spawn(300ms);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	Checks {
		auto& self = handle;
		handle = std::move(self);

		TestAssert( handle != io::invalid_process_handle );

		TestAssert( io::wait(handle, test.ec) == io::wait_status::finished );
		TestAssert( !test.ec );
	}
}

/*!
 * A handle holder that has been moved out of no longer refers to anything
 */
Test(win32_moved_from_handle_is_invalid) {
	using namespace std::chrono;

	process_fixture test{_context};

	auto handle = test.spawn(300ms);

	Preconditions {
		TestAssert( handle != io::invalid_process_handle );
	}

	auto moved = std::move(handle);

	Checks {
		TestAssert( handle == io::invalid_process_handle );
		TestAssert( moved != io::invalid_process_handle );
	}

	io::wait(moved, test.ec);
}
#endif

} // namespace aw
