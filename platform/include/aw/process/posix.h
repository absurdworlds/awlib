#ifndef aw_io_posix_process_h
#define aw_io_posix_process_h

#include <aw/types/array_view.h>
#include <aw/types/support/enum.h>

#include <aw/io/export.h>
#include <aw/io/wait_status.h>

#include <string>
#include <system_error>

namespace aw::io::posix {

enum class process_handle : long {};
constexpr auto invalid_process_handle = process_handle(-1L );

/*!
 * Spawn a child process with specified \a path and argument list \a argv.
 * Argument list must end with `nullptr`.
 */
AW_IO_EXP process_handle spawn(const char* path, aw::array_view<const char*> argv, std::error_code& ec) noexcept;
/*!
 * Spawn a child process with specified argument list \a argv. `argv[0]` is used as path.
 */
AW_IO_EXP process_handle spawn(aw::array_view<const char*> argv, std::error_code& ec) noexcept;

inline process_handle spawn(const char* path, aw::array_view<const char*> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}
inline process_handle spawn(aw::array_view<const char*> argv)
{
	std::error_code ec;
	return spawn(argv, ec);
}
AW_IO_EXP process_handle spawn(std::string path, aw::array_view<std::string> argv, std::error_code& ec);
inline process_handle spawn(std::string path, aw::array_view<std::string> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}

AW_IO_EXP wait_result wait(process_handle pid, std::error_code& ec, timeout_spec_ms timeout = {}) noexcept;
inline wait_result wait(process_handle pid, timeout_spec_ms timeout = {})
{
	std::error_code ec;
	return wait(pid, ec, timeout);
}

AW_IO_EXP int kill(process_handle pid, int signal, std::error_code& ec) noexcept;
inline int kill(process_handle pid, int signal)
{
	std::error_code ec;
	return kill(pid, signal, ec);
}

/*!
 * Stop a process. On POSIX platforms it is equivalent to
 * sending a SIGTERM to the process.
 */
AW_IO_EXP int terminate(process_handle pid, std::error_code& ec) noexcept;
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
} // namespace aw::io::posix
#endif // aw_io_posix_process_h
