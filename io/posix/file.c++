/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/native_file.h>
#include "helpers.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>

#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
#include <sys/ioctl.h>
#include <linux/fs.h>
#endif


namespace aw::io::posix {

file_descriptor open(fs::path const& path, file_mode fm, std::error_code& ec)
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
	auto fd = ::open(path.string().data(), flags, default_mode);

	set_error_if(fd == -1, ec);

	return fd;
}

int close(file_descriptor fd, std::error_code& ec)
{
	int ret = ::close(fd);
	set_error_if(ret == -1, ec);
	return ret;
}

intmax_t read(file_descriptor fd, char* buffer, uintmax_t count, std::error_code& ec)
{
	intmax_t ret;
	do {
		ret = ::read(fd, buffer, count);
	} while (ret == -1 && errno == EINTR);
	set_error_if(ret == -1, ec);
	return ret;
}

intmax_t write(file_descriptor fd, char const* buffer, uintmax_t count, std::error_code& ec)
{
	intmax_t ret = 0;
	uintmax_t left = count;
	do {
		ret = ::write(fd, buffer, left);
		if (ret == -1 && errno == EINTR)
			continue;
		else if (ret == -1)
			break;

		left   -= ret;
		buffer += ret;
	} while (left != 0);

	set_error_if(ret == -1, ec);

	return count - left;
}

intmax_t seek(file_descriptor fd, intmax_t count, seek_mode mode, std::error_code& ec)
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

	auto ret = ::lseek(fd, count, whence);
	set_error_if(ret == -1, ec);

	return ret;
}

intmax_t tell(file_descriptor fd, std::error_code& ec)
{
	return seek(fd, 0, seek_mode::cur, ec);
}

uintmax_t size(file_descriptor fd, std::error_code& ec)
{
	struct stat info;
	int ret = ::fstat(fd, &info);

	set_error_if(ret == -1, ec);

#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
	if (S_ISBLK(info.st_mode)) {
		uint64_t size;
		int ret = ::ioctl(fd, BLKGETSIZE64, &size);
		set_error_if(ret == -1, ec);
		if (ret != -1)
			return uintmax_t(size);
	}
#endif
	return (ret == -1) ? uintmax_t(-1) : info.st_size;
}
} // namespace aw::io::posix
