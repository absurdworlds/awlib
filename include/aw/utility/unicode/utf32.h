/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_utf16_h
#define aw_utility_utf16_h
#include <aw/utility/unicode/unicode.h>
namespace aw {
namespace unicode {
struct utf32 {
using char_type   = char32_t;
using string      = std::u32string;

template<typename Iterator> static
inline Iterator encode(code_point cp, Iterator output)
{
	*(output++) = cp;
	return output;
}

template<typename Iterator> static
inline Iterator decode(Iterator input, Iterator end, code_point& cp)
{
	if (input != end) {
		cp = *(input++);
		return input;
	}
	cp = -1;
	return end;
}
}; // namespace utf16
} // namespace unicode
} // namespace aw
#endif//aw_utility_utf16_h
