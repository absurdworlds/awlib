/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_native_file_h
#define aw_io_native_file_h
#include <aw/io/file_descriptor.h>
#include <aw/io/file_mode.h>
#include <aw/io/export.h>
#include <aw/utility/filesystem.h>
namespace aw {
namespace io {
#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
AW_IO_EXP file_descriptor open(fs::path const& path, file_mode fm, std::error_code& ec);
AW_IO_EXP int close(file_descriptor fd, std::error_code& ec);
AW_IO_EXP intmax_t read(file_descriptor  fd, char* buffer,       uintmax_t count, std::error_code& ec);
AW_IO_EXP intmax_t write(file_descriptor fd, char const* buffer, uintmax_t count, std::error_code& ec);
AW_IO_EXP intmax_t seek(file_descriptor  fd, intmax_t count, seek_mode mode, std::error_code& ec);
AW_IO_EXP intmax_t tell(file_descriptor  fd, std::error_code& ec);
AW_IO_EXP uintmax_t size(file_descriptor fd, std::error_code& ec);

/*! Wrapper around native file handle */
struct file {
	file() = default;
	file(file_descriptor fd) : fd{fd}, owns_fd{false} {}
	inline file(fs::path const& path, file_mode fm, std::error_code& ec) noexcept;
	inline file(fs::path const& path, file_mode fm) noexcept;
	~file() noexcept { close(); }

	file(file const& other) = delete;
	file(file&& other) noexcept { swap(other); }
	file& operator=(file&& other) noexcept { swap(other); }

	bool is_open() const noexcept { return fd != invalid_fd; }

	inline void swap(file& other) noexcept;

	inline void close(std::error_code& ec) noexcept;
	inline void close() noexcept;

	inline intmax_t read(char* buffer, uintmax_t count, std::error_code& ec) noexcept;
	inline intmax_t read(char* buffer, uintmax_t count) noexcept;

	inline intmax_t write(char const* buffer, uintmax_t count, std::error_code& ec) noexcept;
	inline intmax_t write(char const* buffer, uintmax_t count) noexcept;

	inline intmax_t seek(intmax_t count, seek_mode mode, std::error_code& ec) noexcept;
	inline intmax_t seek(intmax_t count, seek_mode mode) noexcept;

	inline intmax_t tell(std::error_code& ec) const noexcept;
	inline intmax_t tell() const noexcept;

	inline uintmax_t size(std::error_code& ec) const noexcept;
	inline uintmax_t size() const noexcept;

private:
	bool owns_fd = true;
	file_descriptor fd = invalid_fd;
};
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
AW_IO_EXP file_descriptor open(fs::path const& path, file_mode fm, std::error_code& ec);
AW_IO_EXP int close(file_descriptor fd, std::error_code& ec);
AW_IO_EXP intmax_t read(file_descriptor  fd, char* buffer,       uintmax_t count, std::error_code& ec);
AW_IO_EXP intmax_t write(file_descriptor fd, char const* buffer, uintmax_t count, std::error_code& ec);
AW_IO_EXP intmax_t seek(file_descriptor  fd, intmax_t count, seek_mode mode, std::error_code& ec);
AW_IO_EXP intmax_t tell(file_descriptor  fd, std::error_code& ec);
AW_IO_EXP uintmax_t size(file_descriptor fd, std::error_code& ec);

/*! Wrapper around native file handle */
struct file {
	file() = default;
	file(file_descriptor fd) : fd{fd}, owns_fd{false} {}
	inline file(fs::path const& path, file_mode fm, std::error_code& ec) noexcept;
	inline file(fs::path const& path, file_mode fm) noexcept;
	~file() noexcept { close(); }

	file(file const& other) = delete;
	file(file&& other) noexcept { swap(other); }
	file& operator=(file&& other) noexcept { swap(other); }

	bool is_open() const noexcept { return fd != invalid_fd; }

	inline void swap(file& other) noexcept;

	inline void close(std::error_code& ec) noexcept;
	inline void close() noexcept;

	inline intmax_t read(char* buffer, uintmax_t count, std::error_code& ec) noexcept;
	inline intmax_t read(char* buffer, uintmax_t count) noexcept;

	inline intmax_t write(char const* buffer, uintmax_t count, std::error_code& ec) noexcept;
	inline intmax_t write(char const* buffer, uintmax_t count) noexcept;

	inline intmax_t seek(intmax_t count, seek_mode mode, std::error_code& ec) noexcept;
	inline intmax_t seek(intmax_t count, seek_mode mode) noexcept;

	inline intmax_t tell(std::error_code& ec) const noexcept;
	inline intmax_t tell() const noexcept;

	inline uintmax_t size(std::error_code& ec) const noexcept;
	inline uintmax_t size() const noexcept;

private:
	file_mode mode = file_mode::none;
	bool owns_fd = true;
	file_descriptor fd = invalid_fd;
};
} // namespace win32
#endif

namespace native {
#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::open;
using posix::close;
using posix::read;
using posix::write;
using posix::seek;
using posix::tell;
using posix::size;
using posix::file;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::open;
using win32::close;
using win32::read;
using win32::write;
using win32::seek;
using win32::tell;
using win32::size;
using win32::file;
#endif
} // namespace native

#include <aw/io/bits/native_file.h>
} // namespace io
} // namespace aw
#endif//aw_io_native_file_h
