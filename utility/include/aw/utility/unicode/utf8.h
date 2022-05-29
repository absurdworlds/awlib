/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_utf8_h
#define aw_utility_utf8_h
#include <aw/utility/unicode/unicode.h>
namespace aw {
namespace unicode {
struct utf8 {
using char_type   = u8;
using string      = std::string;

/*!
 * Returns true if character is a trail character
 */
static bool isTrail(char_type ch) {
	return (ch & 0xC0) == 0x80;
}

/*!
 * Returns width of UTF-8 encoding of specific code point
 */
static size_t width(code_point cp) {
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

static bool isASCII(char_type ch)
{
	return ch < 0x80;
}

static bool isHead(char_type lead)
{
	return (0xC1 < lead) && (lead < 0xF5);
}

/*!
 * Returns how many characters follow the head,
 * or -1 if \a lead is not a valid start of multi-byte encoding
 */
static size_t trailLength(char_type lead) {
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
template<typename Iterator> static
Iterator encode(code_point cp, Iterator output)
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
template<typename Iterator> static
Iterator next(Iterator input, Iterator end)
{
	while ((input < end) && !isHead(*input) && !isASCII(*input))
		++input;

	return input;
}

/*!
 * Decode UTF-8 sequence, if valid
 */
template<typename Iterator> static
Iterator decode(Iterator input, Iterator end, code_point& cp)
{
	// Helper lambda to bail out with an error
	auto error = [&cp] (Iterator ret) {
		cp = -1;
		return ret;
	};

	assert(input < end);

	cp = *(input++) & 0xFF;
	if (cp < 0x80)
		return input;

	size_t length = trailLength(cp);
	if (length == -1)
		return error(input);

	if (std::distance(input, end) < length)
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
}; // namespace utf8
} // namespace unicode
} // namespace aw
#endif//aw_utility_utf8_h
