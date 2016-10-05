/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_utf_convert_
#define _aw_utf_convert_
#include <aw/utility/unicode/utf8.h>
#include <aw/utility/unicode/utf16.h>
#include <aw/utility/unicode/utf32.h>
#include <aw/config.h>
namespace aw {
namespace unicode {
//! Convert string between different Unicode encodings
template<typename Output, typename Input, typename InEnc, typename OutEnc>
Output convert(Output& result, Input const& str, InEnc, OutEnc)
{
	typedef typename Input::const_iterator InIter;
	typedef typename std::back_insert_iterator<Output> OutIter;
	InIter begin = str.begin();
	InIter end   = str.end();

	OutIter out = std::back_inserter(result);

	while (begin != end) {
		code_point cp;

		begin = InEnc::template decode(begin, end, cp);
		if ( !isValidCodepoint(cp) )
			continue;
		out   = OutEnc::template encode(cp, out);
	}

	return result;
}

utf8 getenc(utf8::string const&) { return utf8(); }
utf16 getenc(utf16::string const&) { return utf16(); }
utf32 getenc(utf32::string const&) { return utf32(); }

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
utf16 getenc(std::wstring const&) { return utf16(); }
#else
utf32 getenc(std::wstring const&) { return utf32(); }
#endif

inline std::wstring widen(std::string s)
{
	std::wstring o;
	convert(s, o, getenc(s), getenc(o));
	return o;
}
inline std::string narrow(std::wstring w)
{
	std::string o;
	convert(w, o, getenc(w), getenc(o));
	return o;
}
} // namespace unicode
} // namespace aw
#endif//_aw_utf_convert_
