/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_utf_convert_
#define _hrengin_utf_convert_

#include <string>

#include <hrengin/common/utf.h>
#include <hrengin/common/stringutils.h>

namespace hrengin {
namespace locale {
//! Convert utf-16 character string to utf-8
inline char* narrow(char* output, size_t size,
	wchar_t const* begin, wchar_t const* end)
{
	if(size == 0) {
		return 0;
	}

	-- size;

	while (begin != end) {
		u32 cp = utf16::get<wchar_t const *>(begin, end);

		if (cp == -1) {
			continue;
		}

		size_t width = utf8::width(cp);

		if (size < width) {
			output = 0;
			break;
		}

		utf8::append<char *>(cp, output);
		size -= width;
	}
	*output++ = 0;
	return output;
}

//! Convert utf-8 character string to utf-16
inline wchar_t* widen (wchar_t* output, size_t size,
	char const* begin, char const* end)
{
	if(size == 0) {
		return 0;
	}

	-- size;

	while(begin != end) {
		u32 cp = utf8::get<char const *>(begin, end);

		if(cp == -1) {
			continue;
		}

		size_t width = utf16::width(cp);

		if(size < width) {
			output = 0;
			break;
		}

		utf16::append<wchar_t *>(cp, output);
		size -= width;
	}
	*output++ = 0;
	return output;
}

//! Convert utf-16 wstring to utf-8 string
inline std::string narrow(std::wstring const& str) 
{
	typedef typename std::wstring::const_iterator in_iterator_type;
	typedef typename std::back_insert_iterator<std::string> out_iterator_type;

	std::string result;

	in_iterator_type begin(str.begin());
	in_iterator_type end(str.end());
	out_iterator_type out(result);

	while(begin != end) {
		u32 cp = utf16::get<in_iterator_type>(begin, end);

		if(cp == -1) {
			continue;
		} 

		utf8::append<out_iterator_type>(cp, out);
	}

	return result;
}

//! Convert utf-8 string to utf-16 wstring
inline std::wstring widen(std::string const& str) 
{
	typedef typename std::string::const_iterator in_iterator_type;
	typedef typename std::back_insert_iterator<std::wstring> out_iterator_type;

	std::wstring result;
	in_iterator_type begin(str.begin());
	in_iterator_type end(str.end());
	out_iterator_type out(result);

	while(begin != end) {
		u32 cp = utf8::get<in_iterator_type>(begin, end);

		if(cp == -1) {
			continue;
		} 

		utf16::append<out_iterator_type>(cp, out);
	}

	return result;
}

} // namespace locale
} // namespace hrengin
#endif//_hrengin_utf_convert_
