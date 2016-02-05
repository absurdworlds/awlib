/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_utf16_
#define aw_utility_utf16_
#include <aw/utility/unicode/utf.h>
namespace aw {
namespace unicode {
namespace utf16 {
//! Check if code point is first surrogate
inline bool isFirstSurrogate(u32 cp)
{
	return (cp >= 0xD800 &&
	        cp <= 0xDBFF);
}

//! Check if code point is second surrogate
inline bool isSecondSurrogate(u32 cp)
{
	return (cp >= 0xDC00 &&
	        cp <= 0xDFFF);
}

inline size_t width(u32 cp) {
	if (cp < 0x10000)
		return 1;

	return 2;
}

template<typename Iterator>
inline Iterator encode(u32 cp, Iterator output)
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

template<typename Iterator>
inline Iterator decode(Iterator input, Iterator end, u32& cp)
{
	auto error = [&cp] (Iterator ret) {
		cp = -1;
		return ret;
	};

	u16 first = *(input++);
	if (isFirstSurrogate(first)) {
		u16 second = *(input++);

		if (!isSecondSurrogate(second))
			return error(input);

		cp = ((first  & 0x3FF) << 10) +
		      (second & 0x3FF) + 0x10000;

		return input;
	}

	if (isSecondSurrogate(first))
		return error(input);
	
	cp = first;
	return first;
}
} // namespace utf16
} // namespace unicode
} // namespace aw
#endif//aw_utility_utf16_
