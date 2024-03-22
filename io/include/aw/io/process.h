/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_platform_process_h
#define aw_platform_process_h
#include <aw/io/export.h>
#include <aw/types/array_view.h>

#if defined(AW_SUPPORT_PLATFORM_WIN32)
#include "win32/process.h"
#endif

namespace aw::io {
#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
enum class process_handle : long {

};
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
} // namespace posix
#endif

#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::process_handle;
using posix::invalid_process_handle;
using posix::spawn;
using posix::kill;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::invalid_process_handle;
using win32::process_handle;
using win32::spawn;
using win32::run;
using win32::kill;
using win32::wait;
using win32::executable_name;
#endif
} // namespace aw::platform
#endif//aw_platform_process_h
