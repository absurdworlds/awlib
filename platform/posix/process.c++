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
#include <sys/time.h>
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

namespace {
//! Attributes for posix_spawn that carry out \a flags
struct spawn_attributes {
	explicit spawn_attributes(spawn_flags flags) noexcept
	{
		if (!(flags & spawn_flags::detached))
			return;

		error = posix_spawnattr_init(&attr);
		if (error != 0)
			return;
		initialized = true;

#if defined(POSIX_SPAWN_SETSID)
		error = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSID);
#else
		// without setsid, a new process group is the closest thing
		error = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETPGROUP);
		if (error == 0)
			error = posix_spawnattr_setpgroup(&attr, 0);
#endif
	}

	~spawn_attributes()
	{
		if (initialized)
			posix_spawnattr_destroy(&attr);
	}

	spawn_attributes(spawn_attributes const&) = delete;
	spawn_attributes& operator=(spawn_attributes const&) = delete;

	//! Attributes to pass to posix_spawn, or `nullptr` for the defaults
	const posix_spawnattr_t* get() const noexcept
	{
		return initialized ? &attr : nullptr;
	}

	posix_spawnattr_t attr;
	bool initialized = false;
	int error = 0;
};

//! File actions for posix_spawn that hand the descriptors to the child
struct spawn_file_actions {
	explicit spawn_file_actions(stdio const& streams) noexcept
	{
		const io::posix::file_descriptor redirects[] = { streams.in, streams.out, streams.err };
		for (int target = 0; target < 3; ++target) {
			auto fd = redirects[target];
			if (fd == io::posix::invalid_fd)
				continue;

			// dup2 clears FD_CLOEXEC, so the pipes from io::pipe() survive the exec
			if (!add_dup2(fd, target))
				return;
		}

		for (auto fd : streams.inherit) {
#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_APPLE)
			if (!init())
				return;
			error = posix_spawn_file_actions_addinherit_np(&actions, fd);
			if (error != 0)
				return;
#else
			// dup2 onto itself only clears FD_CLOEXEC (POSIX.1-2024)
			if (!add_dup2(fd, fd))
				return;
#endif
		}
	}

	bool init() noexcept
	{
		if (!initialized) {
			error = posix_spawn_file_actions_init(&actions);
			initialized = (error == 0);
		}
		return initialized;
	}

	bool add_dup2(int fd, int target) noexcept
	{
		if (!init())
			return false;
		error = posix_spawn_file_actions_adddup2(&actions, fd, target);
		return error == 0;
	}

	~spawn_file_actions()
	{
		if (initialized)
			posix_spawn_file_actions_destroy(&actions);
	}

	spawn_file_actions(spawn_file_actions const&) = delete;
	spawn_file_actions& operator=(spawn_file_actions const&) = delete;

	//! Actions to pass to posix_spawn, or `nullptr` if there are none
	const posix_spawn_file_actions_t* get() const noexcept
	{
		return initialized ? &actions : nullptr;
	}

	posix_spawn_file_actions_t actions;
	bool initialized = false;
	int error = 0;
};
} // namespace

AW_PLATFORM_EXP
process_handle spawn(const char* path, aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags, std::error_code& ec) noexcept
{
	// enforce `nullptr` at the end of `argv`
	assert( argv.empty() || argv.back() == nullptr );

	/*
	 * posix_spawnp takes `char* const[]` for historical reasons.
	 * The POSIX spec states that the strings argv[] and envp[] point
	 * to shall not modified, so dropping const here is safe.
	 */
	auto args = const_cast<char* const*>( argv.data() );

	spawn_attributes attr{ flags };
	if (attr.error != 0) {
		ec.assign( attr.error, std::generic_category() );
		return invalid_process_handle;
	}

	spawn_file_actions actions{ streams };
	if (actions.error != 0) {
		ec.assign( actions.error, std::generic_category() );
		return invalid_process_handle;
	}

	// look in the PATH first
	pid_t pid;
	int rc = posix_spawnp(&pid, path, actions.get(), attr.get(), args, environ);

	// try the working directory second
	if (rc == ENOENT)
		rc = posix_spawn(&pid, path, actions.get(), attr.get(), args, environ);

	if (rc != 0) {
		ec.assign( rc, std::generic_category() );
		return invalid_process_handle;
	}

	ec.clear();
	return process_handle( pid );
}

AW_PLATFORM_EXP
process_handle spawn(aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags, std::error_code& ec) noexcept
{
	if (argv.empty() || argv[0] == nullptr) {
		ec = make_error_code( std::errc::invalid_argument );
		return invalid_process_handle;
	}

	return spawn( argv[0], argv, streams, flags, ec );
}

AW_PLATFORM_EXP
process_handle spawn(std::string path, aw::array_view<std::string> argv, stdio const& streams, spawn_flags flags, std::error_code& ec)
{
	std::vector<const char*> args;
	args.push_back(path.data());
	for (std::string const& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, streams, flags, ec);
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
//! The rlimit for \a res, or -1 where this system has none for it
int resource_id(resource res) noexcept
{
	switch (res) {
#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_APPLE)
	// XNU has no address space limit: RLIMIT_AS is an alias of
	// RLIMIT_RSS, and setrlimit() rejects it with EINVAL
	case resource::address_space: return -1;
#else
	case resource::address_space: return RLIMIT_AS;
#endif
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
	auto id = resource_id(res);
	if (id < 0) {
		ec = std::make_error_code(std::errc::not_supported);
		return -1;
	}
	::rlimit native{ to_rlim(value.soft), to_rlim(value.hard) };
	auto ret = ::setrlimit(id, &native);
	set_error_if(ret < 0, ec);
	return ret;
}

AW_PLATFORM_EXP
limit get_limits(resource res, std::error_code& ec) noexcept
{
	auto id = resource_id(res);
	if (id < 0) {
		ec = std::make_error_code(std::errc::not_supported);
		return {};
	}
	::rlimit native{};
	auto ret = ::getrlimit(id, &native);
	set_error_if(ret < 0, ec);
	if (ret < 0)
		return {};
	return { from_rlim(native.rlim_cur), from_rlim(native.rlim_max) };
}


AW_PLATFORM_EXP
std::chrono::microseconds alarm(std::chrono::microseconds delay) noexcept
{
	using namespace std::chrono;

	// alarm(2) and setitimer(2) share the same timer
	auto secs = duration_cast<seconds>(delay);
	itimerval timer = {};
	timer.it_value.tv_sec  = secs.count();
	timer.it_value.tv_usec = (delay - secs).count();

	itimerval previous = {};
	::setitimer(ITIMER_REAL, &timer, &previous);

	return seconds(previous.it_value.tv_sec) + microseconds(previous.it_value.tv_usec);
}
} // namespace self

AW_PLATFORM_EXP
bool is_supported(resource res) noexcept
{
	return self::resource_id(res) >= 0;
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
