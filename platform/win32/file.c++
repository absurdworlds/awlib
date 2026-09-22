/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/native_file.h>
#include <cassert>
#include "winapi_helpers.h"
#include "path.h"
namespace aw::io::win32 {
using platform::win32::close_handle;
using platform::win32::set_error_if;
using platform::win32::winapi_path;

namespace {
int get_access( file_mode mode )
{
	using fm = file_mode;
	int access = 0;
	if (bool(mode & fm::read))
		access |= GENERIC_READ;
	if (bool(mode & fm::write))
		access |= GENERIC_WRITE;
	if (bool(mode & fm::execute))
		access |= GENERIC_EXECUTE;
	return access;
}

int get_openmode( file_mode mode )
{
	using fm = file_mode;
	switch (mode & (fm::create|fm::exclusive|fm::truncate)) {
	case fm::create:
		return OPEN_ALWAYS;
	case fm::create|fm::truncate:
		return CREATE_ALWAYS;
	case fm::create|fm::exclusive:
	case fm::create|fm::exclusive|fm::truncate:
		return CREATE_NEW;
	case fm::truncate:
	case fm::truncate|fm::exclusive:
		return TRUNCATE_EXISTING;
	case fm::exclusive:
	case fm::none:
		return OPEN_EXISTING;
	default:
		assert(!"unreachable");
	};
}

DWORD get_move_method(seek_mode mode)
{
	switch (mode) {
	case seek_mode::set:
		return FILE_BEGIN;
	case seek_mode::end:
		return FILE_END;
	case seek_mode::cur:
		return FILE_CURRENT;
	}

	assert(!"Invalid seek value");
	// intentionally invalid value, SetFilePointerEx should fail
	return DWORD(-1);
}
} // namespace

file_descriptor open(fs::path const& path, file_mode fm, std::error_code& ec)
{
	int access   = get_access( fm );
	int openmode = get_openmode( fm );
	int sharemode = FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE;
	int attrib = FILE_ATTRIBUTE_NORMAL;

	auto handle = CreateFileW( winapi_path{ path }, access, sharemode, NULL, openmode, attrib, NULL);

	set_error_if(handle == INVALID_HANDLE_VALUE, ec);

	return file_descriptor(handle);
}

bool close(file_descriptor fd, std::error_code& ec)
{
	return close_handle( fd, ec );
}

static DWORD clamp_count( uintmax_t count )
{
	constexpr uintmax_t max = std::numeric_limits<DWORD>::max();
	if (count > max)
		return max;
	return static_cast<DWORD>( count );
}

intmax_t read(file_descriptor fd, char* buffer, uintmax_t count, std::error_code& ec)
{
	bool ret = true;
	uintmax_t left = count;
	do {
		DWORD toread = clamp_count( left );
		DWORD nread;
		ret = ::ReadFile(HANDLE(fd), buffer, toread, &nread, NULL);
		if (!ret || nread == 0)
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
		DWORD towrite = clamp_count( left );
		DWORD written;
		ret = ::WriteFile(HANDLE(fd), buffer, towrite, &written, NULL);
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
	const DWORD method = get_move_method(mode);

	LARGE_INTEGER dist;
	LARGE_INTEGER new_fp;
	dist.QuadPart = count;

	bool ret = ::SetFilePointerEx(HANDLE(fd), dist, &new_fp, method);

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
	bool ret = ::GetFileSizeEx( HANDLE(fd), &sz);

	set_error_if(!ret, ec);

	return ret ? sz.QuadPart : uintmax_t(-1);
}
} // namespace aw::io::win32
