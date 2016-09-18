/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_fallback_filesystem_h
#define aw_utility_fallback_filesystem_h
#include <system_error>
#include <aw/utility/unicode/convert.h>
#include <aw/io/io.h>
namespace aw {
namespace filesystem {
/*!
 * Fallback std::filesystem implementation, when none are avaliable.
 * I do not recommend to use it, it is very incomplete,
 * providing enough only to make several basic tests work.
 */
namespace fallback {
struct path {
	path() = default;
	path(path const&) = default;
	path(path&&) = default;

	path(std::string const& source)
		: p(source)
	{ }

	template<class Source>
	path(Source const& source)
	{
		p = unicode::convert<std::string>(source);
	}

	template<class CharT, size_t N>
	path(CharT const (&source)[N])
		: path(std::basic_string<CharT>(source))
	{ }

	std::string string()   const { return p; }
	std::string u8string() const { return p; }

	std::wstring wstring() const { return unicode::convert<std::wstring>(p); }

	bool empty() const { return p.empty(); }

	std::string p;
};

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

	char const* what() const noexcept { return what_str.c_str(); }

private:
	std::string what_str = [this] {
		std::string str = std::system_error::what();
		if (!path1().empty())
			str += " " + path1().string();
		if (!path2().empty())
			str += " " + path2().string();
		return str;
	}();
	path p[2];
};

namespace _impl {
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
namespace win32 {
AW_IO_EXP uintmax_t file_size( path const& p, std::error_code* ec = nullptr );
AW_IO_EXP bool      remove( path const& p,    std::error_code* ec = nullptr );
} // win32
using win32::file_size;
using win32::remove;
#endif
} // _impl

inline auto file_size(path const& p, std::error_code& ec) noexcept
{
	return _impl::file_size(p, &ec);
}

inline auto file_size(path const& p)
{
	return _impl::file_size(p);
}

inline auto remove(path const& p, std::error_code& ec) noexcept
{
	return _impl::remove(p, &ec);
}

inline auto remove(path const& p)
{
	return _impl::remove(p);
}
} // namespace fallback
} // namespace filesystem
} // namespace aw
#endif//aw_utility_fallback_filesystem_h
