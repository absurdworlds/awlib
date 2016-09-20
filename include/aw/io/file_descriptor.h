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
namespace aw {
namespace io {
#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
namespace posix {
using file_descriptor = int;
} // namespace posix
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
namespace win32 {
using file_descriptor = intptr_t;
} // namespace win32
#endif

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::file_descriptor;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::file_descriptor;
#else
using file_descriptor = int;
#endif
} // namespace io
} // namespace aw
