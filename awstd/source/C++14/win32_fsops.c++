/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awstd/filesystem>

#include <utility>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace awstd {
namespace filesystem {
namespace _impl {
namespace win32 {
namespace {
std::error_code last_error()
{
	auto code = static_cast<int>( GetLastError() );
	return {code, std::system_category()};
}
} // namespace

AW_FS_EXP uintmax_t file_size( path const& p, std::error_code* out )
{
	std::wstring const name = p.wstring();

	WIN32_FILE_ATTRIBUTE_DATA info;
	if (!GetFileAttributesExW(name.c_str(), GetFileExInfoStandard, &info)) {
		set_error(out, last_error(), "cannot get file size", p);
		return static_cast<uintmax_t>(-1);
	}

	if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		auto code = std::make_error_code(std::errc::is_a_directory);
		set_error(out, code, "operation not supported", p);
		return static_cast<uintmax_t>(-1);
	}

	clear_error(out);

	return (uintmax_t(info.nFileSizeHigh) << 32) | info.nFileSizeLow;
}

AW_FS_EXP bool exists( path const& p, std::error_code* out)
{
	std::wstring const name = p.wstring();

	auto attrib = GetFileAttributesW(name.c_str());

	if (attrib == INVALID_FILE_ATTRIBUTES) {
		auto error = last_error();
		switch (error.value()) {
		case ERROR_PATH_NOT_FOUND:
		case ERROR_FILE_NOT_FOUND:
		//case ERROR_BAD_PATHNAME:
			clear_error(out);
			return false;
		case ERROR_SHARING_VIOLATION:
			clear_error(out);
			return true; // exists, no access
		default:
			set_error(out, error, "error reading attributes", p);
			return false;
		}
	}

	clear_error(out);

	return true;
}

AW_FS_EXP bool remove( path const& p, std::error_code* out )
{
	if (!exists(p, out))
		return false;

	std::wstring const name = p.wstring();

	if (!DeleteFileW(name.c_str())) {
		set_error(out, last_error(), "cannot remove file", p);
		return false;
	}

	clear_error(out);

	return true;
}

} // namespace win32
} // namespace _impl
} // namespace filesystem
} // namespace awstd
