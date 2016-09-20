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

#define AW_DEFINE_ERRORCODELESS_OVERLOADS(ns) \
void ns::file::close() noexcept \
{ \
	std::error_code ec; \
	close(ec); \
} \
intmax_t ns::file::read(char* buffer, uintmax_t count) noexcept \
{ \
	std::error_code ec; \
	return read(buffer, count, ec); \
} \
intmax_t ns::file::write(char const* buffer, uintmax_t count) noexcept \
{ \
	std::error_code ec; \
	return write(buffer, count, ec); \
} \
intmax_t ns::file::seek(intmax_t count, seek_mode mode) noexcept \
{ \
	std::error_code ec; \
	return seek(count, mode, ec); \
} \
intmax_t ns::file::tell() const noexcept \
{ \
	std::error_code ec; \
	return tell(ec); \
} \
uintmax_t ns::file::size() const noexcept \
{ \
	std::error_code ec; \
	return size(ec); \
}

#if defined(AW_SUPPORT_PLATFORM_POSIX)
posix::file::file(fs::path const& path, file_mode fm, std::error_code& ec) noexcept
{
	fd = posix::open(path, fm, ec);
}
posix::file::file(fs::path const& path, file_mode fm) noexcept
{
	std::error_code ec;
	fd = posix::open(path, fm, ec);
}

void posix::file::swap(file& other) noexcept
{
	std::swap(owns_fd, other.owns_fd);
	std::swap(fd, other.fd);
}

void posix::file::close(std::error_code& ec) noexcept
{
	if (!owns_fd) return;
	if (is_open()) posix::close(fd, ec);
	fd = invalid_fd;
}

intmax_t posix::file::read(char* buffer, uintmax_t count, std::error_code& ec) noexcept
{
	return posix::read(fd, buffer, count, ec);
}

intmax_t posix::file::write(char const* buffer, uintmax_t count, std::error_code& ec) noexcept
{
	return posix::write(fd, buffer, count, ec);
}


intmax_t posix::file::seek(intmax_t count, seek_mode mode, std::error_code& ec) noexcept
{
	return posix::seek(fd, count, mode, ec);
}

intmax_t posix::file::tell(std::error_code& ec) const noexcept
{
	return posix::tell(fd, ec);
}

uintmax_t posix::file::size(std::error_code& ec) const noexcept
{
	return posix::size(fd, ec);
}

AW_DEFINE_ERRORCODELESS_OVERLOADS(posix)
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
win32::file::file(fs::path const& path, file_mode fm, std::error_code& ec) noexcept
{
	fd = win32::open(path, fm, ec);
}
win32::file::file(fs::path const& path, file_mode fm) noexcept
{
	std::error_code ec;
	fd = win32::open(path, fm, ec);
}

void win32::file::swap(file& other) noexcept
{
	std::swap(mode, other.mode);
	std::swap(owns_fd, other.owns_fd);
	std::swap(fd, other.fd);
}

void win32::file::close(std::error_code& ec) noexcept
{
	if (!owns_fd) return;
	if (is_open()) win32::close(fd, ec);
	fd = invalid_fd;
}

intmax_t win32::file::read(char* buffer, uintmax_t count, std::error_code& ec) noexcept
{
	return win32::read(fd, buffer, count, ec);
}

intmax_t win32::file::write(char const* buffer, uintmax_t count, std::error_code& ec) noexcept
{
	if (bool(mode & file_mode::append))
		seek(0, seek_mode::end, ec);
	return win32::write(fd, buffer, count, ec);
}

intmax_t win32::file::seek(intmax_t count, seek_mode mode, std::error_code& ec) noexcept
{
	return win32::seek(fd, count, mode, ec);
}

intmax_t win32::file::tell(std::error_code& ec) const noexcept
{
	return win32::tell(fd, ec);
}

uintmax_t win32::file::size(std::error_code& ec) const noexcept
{
	return win32::size(fd, ec);
}

AW_DEFINE_ERRORCODELESS_OVERLOADS(win32)
#endif

#undef AW_DEFINE_ERRORCODELESS_OVERLOADS
