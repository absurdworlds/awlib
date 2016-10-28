/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_platform_os_name_h
#define aw_platform_os_name_h
#include <aw/platform/export.h>
#include <aw/types/string_view.h>
namespace aw {
namespace platform {
/*!
 * Contains OS version information. Use only to display version to the user.
 */
struct os_name {
	/*! Operating system name, e.g. "Linux" or "Windows XP" */
	std::string sysname;
	/*! Machine name OS is build for, e.g "x86_64" */
	std::string machine;
	/*! OS-specific release number (utsname.release) */
	std::string release;
	/*! OS-specific version string (utsname.version) */
	std::string version;
};

#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
os_name get_os_version();
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
os_name get_os_version();
} // namespace win32
#endif


/*!
 * Get operating system version; intended only for display purpose,
 * (for example, in automatic crash reports)
 * do NOT use it to specify OS-version-specific behavior
 */
#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::get_os_version;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::get_os_version;
#endif
} // namespace platform
} // namespace aw
#endif//aw_platform_os_name_h
