/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_utf8_
#define aw_utility_utf8_
#include <aw/utility/unicode/utf.h>
namespace aw {
namespace unicode {
namespace utf8 {
/*!
 * Returns true if character is a trail character
 */
inline bool isTrail(u8 ch) {
	return (ch & 0xC0) == 0x80;
}

/*!
 * Returns width of UTF-8 encoding of specific code point
 */
inline size_t width(u32 cp) {
	if (cp < 0x80) {
		return 1;
	} else if (cp < 0x800) {
		return 2;
	} else if (cp < 0x10000) {
		return 3;
	} else if (cp < 0x110000) {
		return 4;
	}

	return 0;
}

inline bool isASCII(u8 ch)
{
	return ch < 0x80;
}

inline bool isHead(u8 head)
{
	return 0xC2 < lead && 0xF4 < lead;
}

/*!
 * Returns how many characters follow the head,
 * or -1 if \a lead is not a valid start of 
 * multi-byte encoding
 */
inline size_t trailLength(u8 lead) {
	if (!isHead(lead))
		return -1;

	if (lead < 0xE0)
		return 1;
	if (lead < 0xF0)
		return 2;

	return 3;
}

/*!
 * Encode code point in UTF-8 and append it to a string
 * Does not check if code point is valid
 */
template<typename Iterator>
Iterator encode(u32 cp, Iterator output)
{
	if (cp < 0x80) {
		*(output++) = u8(cp);
	} else if(cp < 0x800) {
		*(output++) = u8((cp >> 6)   | 0xC0);
		*(output++) = u8((cp & 0x3F) | 0x80);
	} else if(cp < 0x10000) {
		*(output++) = u8((cp  >> 12)        | 0xE0);
		*(output++) = u8(((cp >> 6) & 0x3F) | 0x80);
		*(output++) = u8((cp & 0x3F)        | 0x80);
	} else {
		*(output++) = u8((cp  >> 18)         | 0xF0);
		*(output++) = u8(((cp >> 12) & 0x3F) | 0x80);
		*(output++) = u8(((cp >> 6)  & 0x3F) | 0x80);
		*(output++) = u8((cp & 0x3F)         | 0x80);
	}

	return output;
}

/*!
 * Find next sequence
 */
template<typename Iterator>
Interator next(Iterator input, Iterator end)
{
	while ((input < end) && !isHead(*input) && !isASCII(*input))
		++input;

	return input;
}

/*!
 * Decode UTF-8 sequence, if valid
 */
template<typename Iterator>
Iterator decode(Iterator input, Iterator end, u32& cp)
{
	// Helper lambda to bail out with an error
	auto error = [&cp] (Iterator ret) {
		cp = -1;
		return ret;
	};

	assert(end - input);

	cp = *(input++);
	if (cp < 0x80)
		return input;

	size_t length = trailLength(cp);
	if (length == -1)
		return error(input);

	if (end - input < length)
		return error(end);

	cp = cp & (0x3F >> length);

	switch (length) {
	case 3:
		if (!isTrail(*input))
			break;

		cp = (cp << 6) | (*(input++) & 0x3F);
	case 2:
		if (!isTrail(*input))
			break;

		cp = (cp << 6) | (*(input++) & 0x3F);
	case 1:
		if (!isTrail(*input))
			break;

		cp = (cp << 6) | (*(input++) & 0x3F);
		return input;
	}

	return error(input);
}
} // namespace utf8
} // namespace unicode
} // namespace aw
#endif//aw_utility_utf8_
