/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_native_file_h
static_assert(false, "Do not include this file directly.");
#endif

#define AW_DEFINE_COMMON_FUNCTIONS(ns) \
inline ns::file::file(fs::path const& path, file_mode fm, std::error_code& ec) noexcept \
{ \
	fd = ns::open(path, fm, ec); \
} \
inline ns::file::file(fs::path const& path, file_mode fm) noexcept \
{ \
	std::error_code ec; \
	fd = ns::open(path, fm, ec); \
} \
inline void ns::file::close(std::error_code& ec) noexcept \
{ \
	if (!owns_fd) return; \
	if (is_open()) ns::close(fd, ec); \
	fd = invalid_fd; \
} \
inline intmax_t ns::file::read(char* buffer, uintmax_t count, std::error_code& ec) noexcept \
{ \
	return ns::read(fd, buffer, count, ec); \
} \
inline intmax_t ns::file::seek(intmax_t count, seek_mode mode, std::error_code& ec) noexcept \
{ \
	return ns::seek(fd, count, mode, ec); \
} \
inline intmax_t ns::file::tell(std::error_code& ec) const noexcept \
{ \
	return ns::tell(fd, ec); \
} \
inline uintmax_t ns::file::size(std::error_code& ec) const noexcept \
{ \
	return ns::size(fd, ec); \
}

#define AW_DEFINE_ERRORCODELESS_OVERLOADS(ns) \
inline void ns::file::close() noexcept \
{ \
	std::error_code ec; \
	close(ec); \
} \
inline intmax_t ns::file::read(char* buffer, uintmax_t count) noexcept \
{ \
	std::error_code ec; \
	return read(buffer, count, ec); \
} \
inline intmax_t ns::file::write(char const* buffer, uintmax_t count) noexcept \
{ \
	std::error_code ec; \
	return write(buffer, count, ec); \
} \
inline intmax_t ns::file::seek(intmax_t count, seek_mode mode) noexcept \
{ \
	std::error_code ec; \
	return seek(count, mode, ec); \
} \
inline intmax_t ns::file::tell() const noexcept \
{ \
	std::error_code ec; \
	return tell(ec); \
} \
inline uintmax_t ns::file::size() const noexcept \
{ \
	std::error_code ec; \
	return size(ec); \
}

#if defined(AW_SUPPORT_PLATFORM_POSIX)
inline void posix::file::swap(file& other) noexcept
{
	std::swap(owns_fd, other.owns_fd);
	std::swap(fd, other.fd);
}

inline intmax_t posix::file::write(char const* buffer, uintmax_t count, std::error_code& ec) noexcept
{
	return posix::write(fd, buffer, count, ec);
}

AW_DEFINE_COMMON_FUNCTIONS(posix)
AW_DEFINE_ERRORCODELESS_OVERLOADS(posix)
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
inline void win32::file::swap(file& other) noexcept
{
	std::swap(mode, other.mode);
	std::swap(owns_fd, other.owns_fd);
	std::swap(fd, other.fd);
}

inline intmax_t win32::file::write(char const* buffer, uintmax_t count, std::error_code& ec) noexcept
{
	if (bool(mode & file_mode::append))
		seek(0, seek_mode::end, ec);
	return win32::write(fd, buffer, count, ec);
}

AW_DEFINE_COMMON_FUNCTIONS(win32)
AW_DEFINE_ERRORCODELESS_OVERLOADS(win32)
#endif

#undef AW_DEFINE_COMMON_FUNCTIONS
#undef AW_DEFINE_ERRORCODELESS_OVERLOADS
