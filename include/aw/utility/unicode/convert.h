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
#include <aw/utility/string/string.h>
#include <aw/utility/unicode/utf8.h>
#include <aw/utility/unicode/utf16.h>

namespace aw {
namespace unicode {
//! Convert string between different Unicode encodings
template<typename Output, typename Input, typename InEnc, typename OutEnc>
auto convert(Input const& str, InEnc, OutEnc) -> Output
{
	auto begin = std::begin(str);
	auto end   = std::end(str);

	Output result;
	auto out = std::back_inserter(result);

	while (begin != end) {
		code_point cp;

		begin = InEnc::template decode(begin, end, cp);
		if ( !isValidCodepoint(cp) )
			continue;
		out   = OutEnc::template encode(cp, out);
	}

	return result;
}

//! Convert string between different Unicode encodings
template<typename In, typename Out>
auto convert(typename In::string const& str) -> typename Out::string
{
	return convert<typename Out::string>(str, In{}, Out{});
}

constexpr utf8::string(&narrow)(utf16::string const&) = convert<utf16, utf8>;
constexpr utf16::string(&widen)(utf8::string const&)  = convert<utf8, utf16>;
} // namespace unicode
} // namespace aw
#endif//_aw_utf_convert_
