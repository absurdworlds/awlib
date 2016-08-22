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
//! Convert string between different Unicode envodings
template<typename In, typename Out>
auto convert(typename In::string const& str) -> typename Out::string
{
	auto begin = std::begin(str);
	auto end   = std::end(str);

	typename Out::string result;
	auto out = std::back_inserter(result);

	while (begin != end) {
		code_point cp;

		begin = In::template decode(begin, end, cp);
		if ( !isValidCodepoint(cp) )
			continue;
		out   = Out::template encode(cp, out);
	}

	return result;
}

constexpr auto& narrow = convert<utf16, utf8>;
constexpr auto& widen  = convert<utf8, utf16>;
} // namespace unicode
} // namespace aw
#endif//_aw_utf_convert_
