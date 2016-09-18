/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/file.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
namespace aw {
namespace io {
namespace _impl {
namespace win32 {
file::file(file_descriptor fd)
{
	this->fd = fd;
}

file::file(fs::path const& path, file_mode fm)
	: mode(fm)
{
	int access = 0;
	if (bool(fm & file_mode::read))
		access |= GENERIC_READ;
	if (bool(fm & file_mode::write))
		access |= GENERIC_WRITE;

	int openmode = 0;
	if (bool(fm & file_mode::create)) {
		if (bool(fm & file_mode::exclusive))
			openmode = CREATE_NEW;
		else if (bool(fm & file_mode::truncate))
			openmode = CREATE_ALWAYS;
		else
			openmode = OPEN_ALWAYS;
	} else if (bool(fm & file_mode::truncate)) {
		openmode = TRUNCATE_EXISTING;
	} else {
		openmode = OPEN_EXISTING;
	}

	int sharemode = FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE;
	int attrib = FILE_ATTRIBUTE_NORMAL;
	auto handle = CreateFileW(path.wstring().data(), access, sharemode, NULL, openmode, attrib, NULL);

	if (handle == INVALID_HANDLE_VALUE)
		return;

	fd = intptr_t(handle);

	if (!(fm & file_mode::append))
		seek(0, seek_mode::set);
}

void file::swap(file& other) noexcept
{
	std::swap(fd, other.fd);
	std::swap(mode, other.mode);
}

void file::close()
{
	CloseHandle(HANDLE(fd));
	fd   = -1;
}


bool file::is_open() const noexcept
{
	return fd != -1;
}

intmax_t file::read(char* buffer, uintmax_t count)
{
	uintmax_t left = count;
	do {
		unsigned toread = left % std::numeric_limits<unsigned>::max();
		unsigned long nread;
		if (!ReadFile(HANDLE(fd), buffer, toread, &nread, NULL))
			return -1;

		left   -= nread;
		buffer += nread;
	} while (left > 0);

	return count - left;
}

intmax_t file::write(char const* buffer, uintmax_t count)
{
	if (bool(mode & file_mode::append))
		seek(0, seek_mode::end);
	uintmax_t left = count;
	do {
		unsigned towrite = left % std::numeric_limits<unsigned>::max();
		unsigned long written;
		if (!WriteFile(HANDLE(fd), buffer, towrite, &written, NULL))
			return -(count - left);

		left   -= written;
		buffer += written;
	} while (left > 0);

	return count - left;
}

intmax_t file::seek(intmax_t count, seek_mode mode)
{
	int whence;
	switch (mode) {
	case seek_mode::set:
		whence = FILE_BEGIN;
		break;
	case seek_mode::end:
		whence = FILE_END;
		break;
	case seek_mode::cur:
		whence = FILE_CURRENT;
		break;
	}

	LARGE_INTEGER dist;
	LARGE_INTEGER new_fp;
	dist.QuadPart = count;
	if (!SetFilePointerEx(HANDLE(fd), dist, &new_fp, whence))
		return -1;
	return new_fp.QuadPart;
}

intmax_t file::tell()
{
	return seek(0, seek_mode::cur);
}

uintmax_t file::size() const
{
	LARGE_INTEGER sz;
	if (!GetFileSizeEx(HANDLE(fd), &sz))
		return 0;

	return sz.QuadPart;
}
} // namespace win32
} // namespace _impl
} // namespace io
} // namespace aw
