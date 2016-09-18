/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#if !defined(aw_io_file_h)
static_assert(false, "Do not include this file directly");
#endif

/* Platform-specific file implementation details. */

#include <aw/config.h>
#include <aw/io/io.h>
namespace aw {
namespace io {
namespace _impl {
#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
namespace posix {
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
namespace win32 {
#endif

#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using file_descriptor = int;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using file_descriptor = intptr_t;
#else /* unknown platform */
using file_descriptor = int;
#endif

/* Internal file implementation */
class AW_IO_EXP file {
	friend struct aw::io::file;

	file() = default;
	file(file_descriptor fd);
	file(fs::path const& path, file_mode fm);

	file(file const&) = default;
	file& operator=(file const&) = default;

	void swap(file& other) noexcept;

	bool is_open() const noexcept;
	void close();
	intmax_t read(char* buffer, uintmax_t count);
	intmax_t write(char const* buffer, uintmax_t count);
	intmax_t seek(intmax_t count, seek_mode mode);
	intmax_t tell();
	uintmax_t size() const;

	file_descriptor fd = -1;

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
	file_mode mode;
#endif
};

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
} // namespace posix
using posix::file_descriptor;
using posix::file;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
} // namespace win32
using win32::file_descriptor;
using win32::file;
#endif
} // namespace _impl
} // namespace io
} // namespace aw
