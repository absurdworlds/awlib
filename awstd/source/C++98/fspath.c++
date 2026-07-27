/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awstd/filesystem>

namespace awstd {
namespace filesystem {
namespace {
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
const string_view _path_separators("/\\",2);
#else
const string_view _path_separators("/",1);
#endif

template <typename CharT>
bool is_path_separator(CharT c)
{
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
	return c == CharT('/') || c == CharT('\\');
#else
	return c == CharT('/');
#endif
}

std::string& conv_generic(std::string& p)
{
#if __cplusplus >= 201103L
	for (char& c : p) {
		if (is_path_separator(c))
			c = '/';
	}
#else
	for (size_t i = 0, e = p.size(); i < e; ++i) {
		if (is_path_separator(p[i]))
			p[i] = '/';
	}
#endif
	return p;
}

template <typename CharT>
std::basic_string<CharT>& conv_preferred(std::basic_string<CharT>& p)
{
#if __cplusplus >= 201103L
	for (CharT& c : p) {
		if (is_path_separator(c))
			c = static_cast<CharT>(path::preferred_separator);
	}
#else
	for (size_t i = 0, e = p.size(); i < e; ++i) {
		if (is_path_separator(p[i]))
			p[i] = static_cast<CharT>(path::preferred_separator);
	}
#endif
	return p;
}
} // namespace

path& path::make_preferred()
{
	conv_preferred(p);
	return *this;
}

string_view path::path_view() const
{
	return string_view( p );
}

string_view path::filename_view() const
{
	string_view pv = path_view();
	size_t pos = pv.find_last_of(_path_separators);
	if (pos == pv.npos)
		return pv;
	return pv.substr( pos + 1 );
}

namespace {
struct stem_and_ext {
	stem_and_ext(string_view fn) : stem(fn) {}
	stem_and_ext(string_view fn, string_view ext) : stem(fn), ext(ext) {}
	string_view stem;
	string_view ext;
};

stem_and_ext split_filename(string_view fn)
{
	if (fn.empty() || fn == "." || fn == "..")
		return stem_and_ext(fn);
	size_t pos = fn.rfind('.');
	// a leading dot denotes a hidden file, not an extension
	if (pos == fn.npos || pos == 0)
		return stem_and_ext(fn);
	return stem_and_ext( fn.substr(0, pos), fn.substr(pos) );
}
} // namespace

string_view path::stem_view() const
{
	return split_filename(filename_view()).stem;
}

string_view path::extension_view() const
{
	return split_filename(filename_view()).ext;
}

path path::stem() const
{
	return path(stem_view());
}

path path::extension() const
{
	return path(extension_view());
}

std::string path::generic_string() const
{
	std::string s = string();
	return conv_generic(s);
}

std::string path::generic_u8string() const
{
	return generic_string();
}

std::wstring path::native() const
{
	std::wstring str = wstring();
	return conv_preferred(str);
}

} // namespace filesystem
} // namespace awstd
