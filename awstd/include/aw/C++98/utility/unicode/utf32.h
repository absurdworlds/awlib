/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw98_utility_utf32_h
#define aw98_utility_utf32_h
#include <aw/C++98/utility/unicode/unicode.h>
namespace aw {
namespace unicode {
struct utf32 {
typedef code_point char_type;
typedef std::basic_string<char_type> string;

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
}; // namespace utf32
} // namespace unicode
} // namespace aw
#endif//aw98_utility_utf32_h
