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
#if defined(AW_SUPPORT_PLATFORM_POSIX)
#include "posix/process.h"
#endif

namespace aw::io {
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
