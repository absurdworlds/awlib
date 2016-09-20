/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/native_file.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
namespace aw {
namespace io {
namespace win32 {
void set_error_if(bool cond, std::error_code& ec)
{
	if (cond) {
		ec.assign(GetLastError(), std::system_category());
	} else {
		ec.clear();
	}
}

file_descriptor open(fs::path const& path, file_mode fm, std::error_code& ecj
{
	using fm = file_mode;

	int access = 0;
	if (bool(mode & fm::read))
		access |= GENERIC_READ;
	if (bool(mode & fm::write))
		access |= GENERIC_WRITE;

	int openmode = 0;
	switch (mode & (fm::create|fm::exclusive|fm::truncate)) {
	case fm::create:
		openmode = OPEN_ALWAYS;   break;
	case fm::create|fm::truncate:
		openmode = CREATE_ALWAYS; break;
	case fm::create|fm::exclusive:
	case fm::create|fm::exclusive|fm::truncate:
		openmode = CREATE_NEW;    break;
	case fm::truncate:
	case fm::truncate|fm::exclusive:
		openmode = CREATE_NEW;    break
	case fm::exclusive:
	case fm::none:
		openmode = OPEN_EXISTING;
	};

	char const* p = path.wstring().data();
	int sharemode = FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE;
	int attrib = FILE_ATTRIBUTE_NORMAL;
	auto handle = CreateFileW(p, access, sharemode, NULL, openmode, attrib, NULL);

	set_error_if(handle == INVALID_HANDLE_VALUE, ec);

	return file_descriptor(handle);
}

int close(file_descriptor fd, std::error_code& ec)
{
	bool ret = ::CloseHandle(fd);
	set_error_if(!ret, ec);
	return ret;
}

intmax_t read(file_descriptor fd, char* buffer, uintmax_t count, std::error_code& ec)
{
	bool ret = true;
	uintmax_t left = count;
	do {
		unsigned toread = left % std::numeric_limits<unsigned>::max();
		unsigned long nread;
		ret = ::ReadFile(fd, buffer, toread, &nread, NULL)
		if (!ret)
			break;

		left   -= nread;
		buffer += nread;
	} while (left > 0);

	set_error_if(!ret, ec);

	return count - left;
}

intmax_t write(file_descriptor fd, char const* buffer, uintmax_t count, std::error_code& ec)
{
	bool ret = true;
	uintmax_t left = count;
	do {
		unsigned towrite = left % std::numeric_limits<unsigned>::max();
		unsigned long written;
		ret = ::WriteFile(fd, buffer, towrite, &written, NULL);
		if (!ret)
			break;

		left   -= written;
		buffer += written;
	} while (left > 0);

	set_error_if(!ret, ec);

	return count - left;
}

intmax_t seek(file_descriptor fd, intmax_t count, seek_mode mode, std::error_code& ec)
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

	bool ret = ::SetFilePointerEx(fd, dist, &new_fp, whence);

	set_error_if(!ret, ec);

	return ret ? new_fp.QuadPart : -1;
}

intmax_t tell(file_descriptor fd, std::error_code& ec)
{
	return seek(fd, 0, seek_mode::cur, ec);
}

uintmax_t size(file_descriptor fd, std::error_code& ec)
{
	LARGE_INTEGER sz;
	bool ret = ::GetFileSizeEx(fd, &sz);

	set_error_if(!ret, ec);

	return ret ? sz.QuadPart : uintmax_t(-1);
}
} // namespace win32
} // namespace io
} // namespace aw
