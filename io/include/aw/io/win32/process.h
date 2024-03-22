#ifndef aw_io_win32_process_h
#define aw_io_win32_process_h

#include "detail/handle_holder.h"

#include <aw/types/array_view.h>
#include <aw/types/support/enum.h>

#include <aw/io/wait_status.h>

#include <string>
#include <chrono>
#include <system_error>

namespace aw::io::win32 {
enum class process_handle : uintptr_t {};
constexpr auto invalid_process_handle = process_handle(-1);

using process_holder = detail::handle_holder<process_handle>;
using timeout_spec_ms = std::optional<std::chrono::milliseconds>;

inline void close_handle(process_handle handle)
{
	detail::close_handle( underlying(handle) );
}

/*!
 * Spawn a child process with specified \a path and argument list \a argv.
 * Argument list must end with `nullptr`.
 */
AW_IO_EXP process_holder spawn(const char* path, aw::array_view<const char*> argv, std::error_code& ec) noexcept;
/*!
 * Spawn a child process with specified argument list \a argv. `argv[0]` is used as path.
 */
AW_IO_EXP process_holder spawn(aw::array_view<const char*> argv, std::error_code& ec) noexcept;

inline process_holder spawn(const char* path, aw::array_view<const char*> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}
inline process_holder spawn(aw::array_view<const char*> argv)
{
	std::error_code ec;
	return spawn(argv, ec);
}

AW_IO_EXP process_holder spawn(std::string path, aw::array_view<std::string> argv, std::error_code& ec);
inline process_holder spawn(std::string path, aw::array_view<std::string> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}

AW_IO_EXP wait_status wait(process_handle pid, std::error_code& ec, timeout_spec_ms timeout = {}) noexcept;
inline wait_status wait(process_handle pid, timeout_spec_ms timeout = {})
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

inline wait_status run(
	std::string path,
	aw::array_view<std::string> argv,
	std::error_code& ec,
	timeout_spec_ms timeout = {})
{
	auto handle = spawn(path, argv, ec);
	if (handle == invalid_process_handle)
		return wait_status::failed;

	return wait(handle, ec, timeout);
}

inline wait_status run(std::string path, aw::array_view<std::string> argv, timeout_spec_ms timeout = {})
{
	std::error_code ec;
	return run(path, argv, ec, timeout);
}

inline std::string executable_name(std::string path)
{
	if (!path.ends_with(".exe"))
		path += ".exe";
	return path;
}
} // namespace aw::io::win32

#endif // aw_io_win32_process_h
