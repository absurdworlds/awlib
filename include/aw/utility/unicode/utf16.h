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
struct utf16 {
using char_type   = char16_t;
using string      = std::u16string;

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
	auto error = [&cp] (Iterator ret) {
		cp = -1;
		return ret;
	};

	char16_t first = *(input++);
	if (isFirstSurrogate(first)) {
		if (input == end)
			return error(end);

		char16_t second = *(input++);
		if (!isSecondSurrogate(second))
			return error(input);

		cp = ((first  & 0x3FF) << 10) +
		      (second & 0x3FF) + 0x10000;

		return input;
	}

	if (isSecondSurrogate(first))
		return error(input);
	
	cp = first;
	return input;
}
}; // namespace utf16
} // namespace unicode
} // namespace aw
#endif//aw_utility_utf16_h
