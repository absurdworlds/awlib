/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awstd/filesystem>

#include <cerrno>
#include <cstdio>
#include <sys/stat.h>

namespace awstd {
namespace filesystem {
namespace _impl {
namespace posix {
namespace {
std::error_code last_error()
{
	return std::error_code( errno, std::generic_category() );
}

bool is_not_found(std::error_code const& ec)
{
	return ec == std::errc::no_such_file_or_directory
	    || ec == std::errc::not_a_directory;
}
} // namespace

AW_FS_EXP uintmax_t file_size( path const& p, std::error_code* out )
{
	std::string const name = p.u8string();

	struct stat info;
	if (::stat(name.c_str(), &info) == -1) {
		set_error(out, last_error(), "cannot get file size", p);
		return static_cast<uintmax_t>(-1);
	}

	if (!S_ISREG(info.st_mode)) {
		auto code = S_ISDIR(info.st_mode)
			? std::make_error_code(std::errc::is_a_directory)
			: std::make_error_code(std::errc::not_supported);
		set_error(out, code, "cannot get file size", p);
		return static_cast<uintmax_t>(-1);
	}

	clear_error(out);

	return static_cast<uintmax_t>(info.st_size);
}

AW_FS_EXP bool exists( path const& p, std::error_code* out )
{
	std::string const name = p.u8string();

	struct stat info;
	if (::stat(name.c_str(), &info) == -1) {
		auto error = last_error();
		if (!is_not_found(error))
			set_error(out, error, "cannot read file attributes", p);
		else
			clear_error(out);
		return false;
	}

	clear_error(out);

	return true;
}

AW_FS_EXP bool remove( path const& p, std::error_code* out )
{
	std::string const name = p.u8string();

	if (::remove(name.c_str()) == -1) {
		auto error = last_error();
		if (!is_not_found(error)) {
			set_error(out, error, "cannot remove file", p);
			return false;
		}
		clear_error(out);
		return false;
	}

	clear_error(out);

	return true;
}

} // namespace posix
} // namespace _impl
} // namespace filesystem
} // namespace awstd
