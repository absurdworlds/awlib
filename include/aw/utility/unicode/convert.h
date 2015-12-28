/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_utf_convert_
#define _aw_utf_convert_
#include <string>

#include <aw/utility/string/string.h>
#include <aw/utility/unicode/utf.h>

namespace aw {
namespace unicode {
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

} // namespace unicode
} // namespace aw
#endif//_aw_utf_convert_
