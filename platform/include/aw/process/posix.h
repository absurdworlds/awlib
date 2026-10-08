#ifndef aw_process_posix_h
#define aw_process_posix_h

#include <aw/types/array_view.h>
#include <aw/types/support/enum.h>

#include <aw/platform/export.h>
#include <aw/process/spawn_flags.h>
#include <aw/process/wait_status.h>
#include <aw/io/file_descriptor.h>
#include <aw/io/filesystem.h>

#include <string>
#include <vector>
#include <utility>
#include <system_error>

namespace aw::process::posix {

enum class process_handle : long {};
constexpr auto invalid_process_handle = process_handle(-1L );

/*!
 * Descriptors that a child process gets.
 *
 * Each of the standard streams is a descriptor that becomes
 * the stream in the child, or `invalid_fd` to share the caller's.
 *
 * Standard streams are redirected in order: `in`, `out`, then `err`.
 */
struct stdio {
	io::posix::file_descriptor in  = io::posix::invalid_fd;
	io::posix::file_descriptor out = io::posix::invalid_fd;
	io::posix::file_descriptor err = io::posix::invalid_fd;

	/*!
	 * Other descriptors for the child to inherit, under the same number.
	 * The child has to be told about them, e.g. in its arguments.
	 */
	std::vector<io::posix::file_descriptor> inherit;
};

/*!
 * Spawn a child process with specified \a path and argument list \a argv.
 * Argument list must end with `nullptr`.
 * Its standard streams are redirected to \a streams.
 */
AW_PLATFORM_EXP process_handle spawn(const char* path, aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags, std::error_code& ec) noexcept;
/*!
 * Spawn a child process with specified argument list \a argv. `argv[0]` is used as path.
 */
AW_PLATFORM_EXP process_handle spawn(aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags, std::error_code& ec) noexcept;
AW_PLATFORM_EXP process_handle spawn(std::string path, aw::array_view<std::string> argv, stdio const& streams, spawn_flags flags, std::error_code& ec);

inline process_handle spawn(const char* path, aw::array_view<const char*> argv, spawn_flags flags, std::error_code& ec) noexcept
{
	return spawn(path, argv, stdio{}, flags, ec);
}
inline process_handle spawn(aw::array_view<const char*> argv, spawn_flags flags, std::error_code& ec) noexcept
{
	return spawn(argv, stdio{}, flags, ec);
}
inline process_handle spawn(std::string path, aw::array_view<std::string> argv, spawn_flags flags, std::error_code& ec)
{
	return spawn(std::move(path), argv, stdio{}, flags, ec);
}

inline process_handle spawn(const char* path, aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	return spawn(path, argv, spawn_flags::none, ec);
}
inline process_handle spawn(aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	return spawn(argv, spawn_flags::none, ec);
}
inline process_handle spawn(std::string path, aw::array_view<std::string> argv, std::error_code& ec)
{
	return spawn(std::move(path), argv, spawn_flags::none, ec);
}

inline process_handle spawn(const char* path, aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags = spawn_flags::none)
{
	std::error_code ec;
	return spawn(path, argv, streams, flags, ec);
}
inline process_handle spawn(aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags = spawn_flags::none)
{
	std::error_code ec;
	return spawn(argv, streams, flags, ec);
}
inline process_handle spawn(std::string path, aw::array_view<std::string> argv, stdio const& streams, spawn_flags flags = spawn_flags::none)
{
	std::error_code ec;
	return spawn(std::move(path), argv, streams, flags, ec);
}

inline process_handle spawn(const char* path, aw::array_view<const char*> argv, spawn_flags flags = spawn_flags::none)
{
	std::error_code ec;
	return spawn(path, argv, flags, ec);
}
inline process_handle spawn(aw::array_view<const char*> argv, spawn_flags flags = spawn_flags::none)
{
	std::error_code ec;
	return spawn(argv, flags, ec);
}
inline process_handle spawn(std::string path, aw::array_view<std::string> argv, spawn_flags flags = spawn_flags::none)
{
	std::error_code ec;
	return spawn(std::move(path), argv, flags, ec);
}

AW_PLATFORM_EXP wait_result wait(process_handle pid, std::error_code& ec, timeout_spec_ms timeout = {}) noexcept;
inline wait_result wait(process_handle pid, timeout_spec_ms timeout = {})
{
	std::error_code ec;
	return wait(pid, ec, timeout);
}

AW_PLATFORM_EXP int kill(process_handle pid, int signal, std::error_code& ec) noexcept;
inline int kill(process_handle pid, int signal)
{
	std::error_code ec;
	return kill(pid, signal, ec);
}

/*!
 * Stop a process. On POSIX platforms it is equivalent to
 * sending a SIGTERM to the process.
 */
AW_PLATFORM_EXP int terminate(process_handle pid, std::error_code& ec) noexcept;
inline int terminate(process_handle pid)
{
	std::error_code ec;
	return terminate(pid, ec);
}

inline wait_result run(
	std::string path,
	aw::array_view<std::string> argv,
	std::error_code& ec,
	timeout_spec_ms timeout = {})
{
	auto handle = spawn(path, argv, ec);
	if (handle == invalid_process_handle)
		return { .status = wait_status::failed };

	return wait(handle, ec, timeout);
}

inline wait_result run(std::string path, aw::array_view<std::string> argv, timeout_spec_ms timeout = {})
{
	std::error_code ec;
	return run(path, argv, ec, timeout);
}

inline std::string executable_name(std::string path)
{
	return path;
}

namespace self {
/*!
 * Returns the path of the current executable.
 */
AW_PLATFORM_EXP fs::path path(std::error_code& ec);
inline fs::path path()
{
	std::error_code ec;
	return path(ec);
}
} // namespace self
} // namespace aw::process::posix
#endif // aw_process_posix_h
