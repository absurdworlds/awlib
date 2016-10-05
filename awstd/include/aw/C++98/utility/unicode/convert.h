/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw98_utf_convert_h
#define aw98_utf_convert_h
#include <_c++config>
#include <aw/C++98/utility/unicode/utf8.h>
#include <aw/C++98/utility/unicode/utf16.h>
#include <aw/C++98/utility/unicode/utf32.h>
namespace aw {
namespace unicode {
//! Convert string between different Unicode encodings
template<typename Input, typename Output, typename InEnc, typename OutEnc>
Output& convert(Input const& str, Output& result, InEnc, OutEnc)
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

inline utf8 getenc(utf8::string const&) { return utf8(); }
inline utf16 getenc(utf16::string const&) { return utf16(); }
inline utf32 getenc(utf32::string const&) { return utf32(); }

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
inline utf16 getenc(std::wstring const&) { return utf16(); }
#else
inline utf32 getenc(std::wstring const&) { return utf32(); }
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
#endif//aw98_utf_convert_h
