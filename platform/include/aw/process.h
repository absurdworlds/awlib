/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_process_h
#define aw_process_h
#include <aw/platform/export.h>
#include <aw/types/array_view.h>

#if defined(AW_SUPPORT_PLATFORM_WIN32)
#include <aw/process/win32.h>
#endif
#if defined(AW_SUPPORT_PLATFORM_POSIX)
#include <aw/process/posix.h>
#endif

namespace aw::process {
/*
 * Functions in this namespace apply to the calling process,
 * i.e. the current process as opposed to a child of it.
 */
namespace self {}

#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::process_handle;
using posix::invalid_process_handle;
using posix::spawn;
using posix::kill;
using posix::terminate;
using posix::wait;
using posix::run;
using posix::executable_name;
namespace self {
using posix::self::path;
} // namespace self
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::invalid_process_handle;
using win32::process_handle;
using win32::spawn;
using win32::kill;
using win32::terminate;
using win32::wait;
using win32::run;
using win32::executable_name;
namespace self {
using win32::self::handle;
#if defined(AW_PROCESS_HAS_HANDLE_COUNT)
using win32::self::handle_count;
#endif
using win32::self::path;
} // namespace self
#endif
} // namespace aw::process
#endif//aw_process_h
