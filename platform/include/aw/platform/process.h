/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_platform_demangle_h
#define aw_platform_demangle_h
#include <aw/platform/export.h>
#include <aw/types/array_view.h>
#include <system_error>
#include <string>
namespace aw::platform {
#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
enum class process_handle : long {

};
constexpr auto invalid_process_handle = process_handle(-1L );

/*!
 * Spawn a child process with specified \a path and argument list \a argv.
 * Argument list must end with `nullptr`.
 */
AW_PLATFORM_EXP process_handle spawn(const char* path, aw::array_ref<char*> argv, std::error_code& ec) noexcept;
/*!
 * Spawn a child process with specified argument list \a argv. `argv[0]` is used as path.
 */
AW_PLATFORM_EXP process_handle spawn(aw::array_ref<char*> argv, std::error_code& ec) noexcept;
AW_PLATFORM_EXP int kill(process_handle pid, int signal, std::error_code& ec) noexcept;

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
AW_PLATFORM_EXP process_handle spawn(std::string path, aw::array_ref<std::string> argv);

inline int kill(process_handle pid, int signal)
{
	std::error_code ec;
	return kill(pid, signal, ec);
}
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
enum class process_handle : uintptr_t {};
constexpr auto invalid_process_handle = process_handle(-1);

/*!
 * Spawn a child process with specified \a path and argument list \a argv.
 * Argument list must end with `nullptr`.
 */
AW_PLATFORM_EXP process_handle spawn(const char* path, aw::array_ref<const char*> argv, std::error_code& ec) noexcept;
AW_PLATFORM_EXP process_handle spawn(std::string path, aw::array_ref<std::string> argv, std::error_code& ec);
/*!
 * Spawn a child process with specified argument list \a argv. `argv[0]` is used as path.
 */
AW_PLATFORM_EXP process_handle spawn(aw::array_ref<const char*> argv, std::error_code& ec) noexcept;
AW_PLATFORM_EXP int kill(process_handle pid, int signal, std::error_code& ec) noexcept;

inline process_handle spawn(const char* path, aw::array_ref<const char*> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}
inline process_handle spawn(aw::array_ref<const char*> argv)
{
	std::error_code ec;
	return spawn(argv, ec);
}

inline process_handle spawn(std::string path, aw::array_ref<std::string> argv)
{
	std::error_code ec;
	return spawn(path, argv, ec);
}

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
using win32::process_handle;
using win32::invalid_process_handle;
using win32::spawn;
using win32::kill;
#endif
} // namespace aw::platform
#endif//aw_platform_demangle_h
