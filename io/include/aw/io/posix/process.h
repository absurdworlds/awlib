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
AW_IO_EXP process_handle spawn(const char* path, aw::array_ref<char*> argv, std::error_code& ec) noexcept;
/*!
 * Spawn a child process with specified argument list \a argv. `argv[0]` is used as path.
 */
AW_IO_EXP process_handle spawn(aw::array_ref<char*> argv, std::error_code& ec) noexcept;
AW_IO_EXP int kill(process_handle pid, int signal, std::error_code& ec) noexcept;

inline process_handle spawn(const char* path, aw::array_ref<char*> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}
inline process_handle spawn(aw::array_ref<char*> argv)
{
	std::error_code ec;
	return spawn(argv, ec);
}
AW_IO_EXP process_handle spawn(std::string path, aw::array_ref<std::string> argv);

inline int kill(process_handle pid, int signal)
{
	std::error_code ec;
	return kill(pid, signal, ec);
}
} // namespace aw::io::posix
#endif // aw_io_posix_process_h
