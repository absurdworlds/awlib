#include <aw/process/posix.h>
#include <aw/process/posix/alarm.h>
#include <aw/process/posix/fork.h>
#include <aw/process/limits.h>

#include "helpers.h"

#include <aw/types/string_view.h>
#include <aw/algorithm/in.h>

#include <algorithm>
#include <chrono>
#include <vector>

#include <cassert>
#include <cerrno>
#include <cstring>
#include <ctime>

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <spawn.h>
#include <unistd.h>
#include <signal.h>

#ifdef __APPLE__
#include <mach-o/dyld.h>
extern char** environ;
#endif

namespace aw::process::posix {
using platform::posix::set_error;
using platform::posix::set_error_if;

AW_PLATFORM_EXP
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

	// look in the PATH first
	pid_t pid;
	int rc = posix_spawnp(&pid, path, nullptr, nullptr, args, environ);

	// try the working directory second
	if (rc == ENOENT)
		rc = posix_spawn(&pid, path, nullptr, nullptr, args, environ);

	if (rc != 0) {
		ec.assign( rc, std::generic_category() );
		return invalid_process_handle;
	}

	ec.clear();
	return process_handle( pid );
}

AW_PLATFORM_EXP
process_handle spawn(aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	if (argv.empty() || argv[0] == nullptr) {
		ec = make_error_code( std::errc::invalid_argument );
		return invalid_process_handle;
	}

	return spawn( argv[0], argv, ec );
}

AW_PLATFORM_EXP
process_handle spawn(std::string path, aw::array_view<std::string> argv, std::error_code& ec)
{
	std::vector<const char*> args;
	args.push_back(path.data());
	for (std::string const& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, ec);
}

AW_PLATFORM_EXP
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

AW_PLATFORM_EXP
int terminate(process_handle pid, std::error_code& ec) noexcept
{
	return kill(pid, SIGTERM, ec);
}

AW_PLATFORM_EXP
process_handle fork(std::error_code& ec) noexcept
{
	auto pid = ::fork();
	set_error_if(pid < 0, ec);
	return pid < 0 ? invalid_process_handle : process_handle(pid);
}

namespace self {
AW_PLATFORM_EXP
void exit_now(int code) noexcept
{
	::_exit(code);
}
} // namespace self

namespace self {
AW_PLATFORM_EXP
fs::path path(std::error_code& ec)
{
#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
	// readlink() does not terminate the result and truncates silently,
	// so keep growing until the link fits with room to spare
	std::string buf(256, '\0');
	while (true) {
		auto len = ::readlink("/proc/self/exe", buf.data(), buf.size());
		if (len < 0) {
			set_error(ec);
			return {};
		}
		if (size_t(len) < buf.size()) {
			buf.resize(size_t(len));
			ec.clear();
			return fs::path{ std::move(buf) };
		}
		buf.resize(buf.size() * 2);
	}
#elif (AW_PLATFORM_SPECIFIC == AW_PLATFORM_APPLE)
	uint32_t size = 0;
	std::string buf;
	while (_NSGetExecutablePath(buf.data(), &size) != 0)
		buf.resize(size);
	buf.resize( std::strlen(buf.data()) );

	// Canonicalize path, as it might be relative or contain symlinks
	return fs::canonical(fs::path{ std::move(buf) }, ec);
#else
	// TODO: BSD has sysctl(KERN_PROC_PATHNAME)
	// https://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
	ec = std::make_error_code(std::errc::function_not_supported);
	return {};
#endif
}

namespace {
int resource_id(resource res) noexcept
{
	switch (res) {
	case resource::address_space: return RLIMIT_AS;
	case resource::stack:         return RLIMIT_STACK;
	case resource::core_file:     return RLIMIT_CORE;
	case resource::cpu_time:      return RLIMIT_CPU;
	case resource::open_files:    return RLIMIT_NOFILE;
	}
	return -1;
}

rlim_t to_rlim(uintmax_t value) noexcept
{
	return value == unlimited ? RLIM_INFINITY : rlim_t(value);
}

uintmax_t from_rlim(rlim_t value) noexcept
{
	return value == RLIM_INFINITY ? unlimited : uintmax_t(value);
}
} // namespace

AW_PLATFORM_EXP
int set_limits(resource res, limit value, std::error_code& ec) noexcept
{
	::rlimit native{ to_rlim(value.soft), to_rlim(value.hard) };
	auto ret = ::setrlimit(resource_id(res), &native);
	set_error_if(ret < 0, ec);
	return ret;
}

AW_PLATFORM_EXP
limit get_limits(resource res, std::error_code& ec) noexcept
{
	::rlimit native{};
	auto ret = ::getrlimit(resource_id(res), &native);
	set_error_if(ret < 0, ec);
	if (ret < 0)
		return {};
	return { from_rlim(native.rlim_cur), from_rlim(native.rlim_max) };
}


AW_PLATFORM_EXP
std::chrono::seconds alarm(std::chrono::seconds delay) noexcept
{
	return std::chrono::seconds( ::alarm( unsigned(delay.count()) ) );
}
} // namespace self

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
//! Decode what waitpid() reported about a process that has ended
wait_result decode_status(int status) noexcept
{
	wait_result result{ .status = wait_status::finished };

	if (WIFEXITED(status))
		result.code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		result.signal = WTERMSIG(status);

	return result;
}

wait_result wait_until(pid_t pid, std::chrono::steady_clock::time_point deadline,
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
			return decode_status( status );

		if (ret < 0 && errno != EINTR) {
			set_error( ec );
			return { .status = wait_status::failed };
		}

		const auto left = deadline - steady_clock::now();
		if (left <= steady_clock::duration::zero())
			return { .status = wait_status::timeout };

		sleep_for( std::min<nanoseconds>(interval, left) );
		interval = std::min(interval * 2, max_interval);
	}
}
} // namespace

AW_PLATFORM_EXP wait_result wait(process_handle pid, std::error_code& ec, timeout_spec_ms timeout) noexcept
{
	ec.clear();

	if (timeout)
		return wait_until( pid_t(pid), std::chrono::steady_clock::now() + *timeout, ec );

	int status = 0;

	pid_t ret;
	do
		ret = waitpid( pid_t(pid), &status, 0);
	while (ret < 0 && errno == EINTR);

	if (ret < 0) {
		set_error( ec );
		return { .status = wait_status::failed };
	}

	return decode_status( status );
}
} // namespace aw::process::posix
