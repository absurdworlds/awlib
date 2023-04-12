/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifdef aw_utility_fallback_filesystem_h
#include <string_view>
#include <awstd/_c++config>
#include <aw/C++98/utility/unicode/convert.h>

//------------------------------------------------------------------------------
#ifdef AWSTD_MODULE_FS
#define AW_FS_EXP AW_EXPORT
#else
#define AW_FS_EXP AW_IMPORT
#endif

namespace awstd {
namespace filesystem {
struct path {
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
	static aw_constexpr char preferred_separator = '\\';
#else
	static aw_constexpr char preferred_separator = '/';
#endif

	path() {}
	path(path const& other) : p(other.p) {}
#if __cplusplus >= 201103L
	path(path&& other) : p{std::move(other.p)} {}
#endif

	path(string_view source)
		: p(std::string(source))
	{ }

	path(std::string const& source)
		: p(source)
	{ }

	path(std::wstring const& source)
		: p(aw::unicode::narrow(source))
	{ }

	template<class CharT, size_t N>
	path(CharT const (&source)[N])
		: path(std::basic_string<CharT>(source))
	{ }

	path& make_preferred();

	path filename() const  { return filename_view(); }
	//! Filename without extension: "file.txt" -> "file"
	path stem() const;
	//! Extract extension: "file.txt" -> ".txt"
	path extension() const;

	std::string generic_string() const;
	std::string generic_u8string() const;

	std::string string()   const  { return p; }
	std::string u8string() const  { return p; }

	std::wstring wstring() const { return aw::unicode::widen(p); }

	std::string generic() const { return generic_u8string(); }
	std::wstring native() const;

	bool empty() const { return p.empty(); }

protected:
	string_view path_view() const;
	string_view filename_view() const;
	string_view stem_view() const;
	string_view extension_view() const;

private:
	std::string p;
};
} // namespace filesystem
} // namespace awstd
#endif//aw_utility_fallback_filesystem_h
