/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw98_utility_utf16_h
#define aw98_utility_utf16_h
#include <aw/C++98/utility/unicode/unicode.h>
namespace aw {
namespace unicode {
struct utf16 {
typedef unsigned short char_type;
typedef std::basic_string<char_type> string;

//! Check if code point is first surrogate
static bool isFirstSurrogate(code_point cp)
{
	return (cp >= 0xD800 &&
	        cp <= 0xDBFF);
}

//! Check if code point is second surrogate
static bool isSecondSurrogate(code_point cp)
{
	return (cp >= 0xDC00 &&
	        cp <= 0xDFFF);
}

static size_t width(code_point cp) {
	if (cp < 0x10000)
		return 1;

	return 2;
}

template<typename Iterator> static
inline Iterator encode(code_point cp, Iterator output)
{
	if (cp < 0x10000) {
		*(output++) = cp;
	} else {
		cp -= 0x10000;
		*(output++) = 0xDC00 + (cp >> 10);
		*(output++) = 0xDC00 + (cp & 0x3FF);
	}

	return output;
}

template<typename Iterator> static
inline Iterator decode(Iterator input, Iterator end, code_point& cp)
{
	char_type first = *(input++);
	if (isFirstSurrogate(first)) {
		if (input == end) {
			cp = -1;
			return input;
		}

		char_type second = *(input++);
		if (!isSecondSurrogate(second))
			return error(input);

		cp = ((first  & 0x3FF) << 10) +
		      (second & 0x3FF) + 0x10000;

		return input;
	}

	if (isSecondSurrogate(first)) {
		cp = -1;
		return input;
	}
	
	cp = first;
	return input;
}
}; // namespace utf16
} // namespace unicode
} // namespace aw
#endif//aw98_utility_utf16_h
