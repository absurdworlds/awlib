#include "aw/io/posix/process.h"

#include "helpers.h"

#include <aw/types/string_view.h>
#include <aw/algorithm/in.h>

#include <algorithm>
#include <chrono>
#include <vector>

#include <cassert>
#include <ctime>

#include <sys/types.h>
#include <sys/wait.h>
#include <spawn.h>
#include <unistd.h>
#include <signal.h>

#ifdef __APPLE__
extern char** environ;
#endif

namespace aw::io::posix {
AW_IO_EXP
process_handle spawn(const char* path, aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	// enforce `nullptr` at the end of `argv`
	assert( argv.empty() || argv.back() == nullptr );

	/*
	 * posix_spawnp takes `char* const[]` for historical reasons.
	 * The POSIX spec states that the strings argv[] and envp[] point
	 * to shall not modified, so dropping const here is safe.
	 */
	auto args = const_cast<char* const*>( argv.data() );

	pid_t pid;
	int rc = posix_spawnp(&pid, path, nullptr, nullptr, args, environ);
	if (rc == 2)
		rc = posix_spawn(&pid, path, nullptr, nullptr, args, environ);

	if (rc == 0)
		return process_handle( pid );

	ec.assign( rc, std::generic_category() );
	return invalid_process_handle;
}

AW_IO_EXP
process_handle spawn(aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	if (argv.empty() || argv[0] == nullptr) {
		ec = make_error_code( std::errc::invalid_argument );
		return invalid_process_handle;
	}

	return spawn( argv[0], argv, ec );
}

AW_IO_EXP
process_handle spawn(std::string path, aw::array_view<std::string> argv, std::error_code& ec)
{
	std::vector<const char*> args;
	args.push_back(path.data());
	for (std::string const& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, ec);
}

AW_IO_EXP
int kill(process_handle pid, int signal, std::error_code& ec) noexcept
{
	// TODO: don't accept -1 or 0 as pid, add separate functions for that
	if( in( pid, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return -1;
	};

	auto ret = ::kill( pid_t(pid), signal);
	set_error_if(ret < 0, ec);
	return ret;
}

namespace {
// this one is noexcept unlike std::this_thread::sleep_for
void sleep_for(std::chrono::nanoseconds duration) noexcept
{
	using namespace std::chrono;

	timespec spec = {};
	spec.tv_sec  = duration_cast<seconds>(duration).count();
	spec.tv_nsec = (duration % seconds(1)).count();

	// an interrupted sleep is fine since the caller re-checks the deadline
	nanosleep(&spec, nullptr);
}

/*!
 * Wait until the child changes state or \a deadline passes.
 */
wait_status wait_until(pid_t pid, std::chrono::steady_clock::time_point deadline,
                       std::error_code& ec) noexcept
{
	// TODO: use pidfd_open and ppoll on Linux instead of polling
	using namespace std::chrono;

	constexpr auto max_interval = microseconds(10'000);
	auto interval = microseconds(200);

	for (;;) {
		int status = 0;
		const pid_t ret = waitpid( pid, &status, WNOHANG );
		if (ret > 0)
			return wait_status::finished;

		if (ret < 0 && errno != EINTR) {
			ec.assign( errno, std::generic_category() );
			return wait_status::failed;
		}

		const auto left = deadline - steady_clock::now();
		if (left <= steady_clock::duration::zero())
			return wait_status::timeout;

		sleep_for( std::min<nanoseconds>(interval, left) );
		interval = std::min(interval * 2, max_interval);
	}
}
} // namespace

AW_IO_EXP wait_status wait(process_handle pid, std::error_code& ec, timeout_spec_ms timeout) noexcept
{
	if (timeout)
		return wait_until( pid_t(pid), std::chrono::steady_clock::now() + *timeout, ec );

	int status = 0;

	pid_t ret;
	do
		ret = waitpid( pid_t(pid), &status, 0);
	while (ret < 0 && errno == EINTR);

	if (ret < 0) {
		ec.assign( errno, std::generic_category() );
		return wait_status::failed;
	}
	return wait_status::finished;
}
} // namespace aw::platform::posix
