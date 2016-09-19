/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/file.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
namespace aw {
namespace io {
namespace _impl {
namespace posix {
file::file(file_descriptor fd)
{
	if ((fcntl(fd, F_GETFD) == -1) && errno == EBADF)
		return;

	this->fd = fd;
}

file::file(fs::path const& path, file_mode fm)
{
	int flags = 0;
	switch (fm & (file_mode::read | file_mode::write)) {
	case file_mode::read:
		flags |= O_RDONLY; break;
	case file_mode::write:
		flags |= O_WRONLY; break;
	case file_mode::read|file_mode::write:
		flags |= O_RDWR;   break;
	}

	if (bool(fm & file_mode::append))
		flags |= O_APPEND;
	if (bool(fm & file_mode::create))
		flags |= O_CREAT;
	if (bool(fm & file_mode::truncate))
		flags |= O_TRUNC;
	if (bool(fm & file_mode::exclusive))
		flags |= O_EXCL;

	constexpr mode_t default_mode = 0644;
	fd = open(path.u8string().data(), flags, default_mode);
}

void file::swap(file& other) noexcept
{
	std::swap(fd, other.fd);
}

void file::close()
{
	::close(fd);
	fd   = -1;
}


bool file::is_open() const noexcept
{
	return fd != -1;
}

intmax_t file::read(char* buffer, uintmax_t count)
{
	intmax_t ret;
	do {
		ret = ::read(fd, buffer, count);
	} while (ret == -1 && errno == EINTR);
	return ret;
}

intmax_t file::write(char const* buffer, uintmax_t count)
{
	uintmax_t left = count;
	do {
		auto ret = ::write(fd, buffer, left);
		if (ret == -1 && errno == EINTR)
			continue;
		else if (ret == -1)
			return -(count - left);

		left   -= ret;
		buffer += ret;
	} while (left != 0);

	return count - left;
}

intmax_t file::seek(intmax_t count, seek_mode mode)
{
	int whence;
	switch (mode) {
	case seek_mode::set:
		whence = SEEK_SET;
		break;
	case seek_mode::end:
		whence = SEEK_END;
		break;
	case seek_mode::cur:
		whence = SEEK_CUR;
		break;
	}

	return ::lseek(fd, count, whence);
}

intmax_t file::tell()
{
	return seek(0, seek_mode::cur);
}

uintmax_t file::size() const
{
	if (!is_open())
		return 0;

	struct stat info;
	fstat(fd, &info);
	return info.st_size;
}
} // namespace posix
} // namespace _impl
} // namespace io
} // namespace aw
