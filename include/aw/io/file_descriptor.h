/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_file_descriptor_h
#define aw_io_file_descriptor_h
#include <aw/config.h>
namespace aw {
namespace io {
#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
using file_descriptor = int;
constexpr file_descriptor invalid_fd = file_descriptor(-1);
} // namespace posix
#endif
#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
using file_descriptor = void*;
constexpr file_descriptor invalid_fd = file_descriptor(-1);
} // namespace win32
#endif

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::file_descriptor;
using posix::invalid_fd;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::file_descriptor;
using win32::invalid_fd;
#else
using file_descriptor = int;
constexpr file_descriptor invalid_fd = -1;
#endif
} // namespace io
} // namespace aw
#endif//aw_io_file_descriptor_h
