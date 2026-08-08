/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifdef awstd_filesystem_h
#include <cstdint>
#include <string>
#include <system_error>
#include <utility>

namespace awstd {
namespace filesystem {

struct filesystem_error : std::system_error {
	filesystem_error( std::string const& what_arg, std::error_code ec )
		: system_error{ec, what_arg}
	{}

	filesystem_error( std::string const& what_arg,
	                  path const& p1,
	                  std::error_code ec )
		: system_error{ec, what_arg}, p{p1}
	{}

	filesystem_error( std::string const& what_arg,
	                  path const& p1,
	                  path const& p2,
	                  std::error_code ec )
		: system_error{ec, what_arg}, p{p1, p2}
	{}

	path const& path1() const { return p[0]; }
	path const& path2() const { return p[1]; }

	char const* what() const noexcept override { return what_str.c_str(); }

private:
	// NOTE: p is initialized before what_str, which reads it
	path p[2];

	std::string what_str = [this] {
		std::string str = std::system_error::what();
		if (!path1().empty())
			str += " " + path1().string();
		if (!path2().empty())
			str += " " + path2().string();
		return str;
	}();
};


namespace _impl {
/*!
 * Report an error: either through \a out, or, when the caller
 * did not provide an error_code, by throwing filesystem_error.
 */
template<typename...Args>
void set_error( std::error_code* out, std::error_code code, Args&&...args)
{
	if (!out)
		throw filesystem_error{ std::forward<Args>(args)..., code };
	*out = code;
}

inline void clear_error(std::error_code* out)
{
	if (out) out->clear();
}

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
namespace win32 {
AW_FS_EXP uintmax_t file_size( path const& p, std::error_code* ec = nullptr );
AW_FS_EXP bool      exists( path const& p,    std::error_code* ec = nullptr );
AW_FS_EXP bool      remove( path const& p,    std::error_code* ec = nullptr );
} // namespace win32
using win32::file_size;
using win32::exists;
using win32::remove;
#else
namespace posix {
AW_FS_EXP uintmax_t file_size( path const& p, std::error_code* ec = nullptr );
AW_FS_EXP bool      exists( path const& p,    std::error_code* ec = nullptr );
AW_FS_EXP bool      remove( path const& p,    std::error_code* ec = nullptr );
} // namespace posix
using posix::file_size;
using posix::exists;
using posix::remove;
#endif
} // namespace _impl

inline auto file_size(path const& p, std::error_code& ec) noexcept
{
	return _impl::file_size(p, &ec);
}

inline auto file_size(path const& p)
{
	return _impl::file_size(p);
}

inline auto exists(path const& p, std::error_code& ec) noexcept
{
	return _impl::exists(p, &ec);
}

inline auto exists(path const& p)
{
	return _impl::exists(p);
}

inline auto remove(path const& p, std::error_code& ec) noexcept
{
	return _impl::remove(p, &ec);
}

inline auto remove(path const& p)
{
	return _impl::remove(p);
}
} // namespace filesystem
} // namespace awstd
#endif//awstd_filesystem_h
