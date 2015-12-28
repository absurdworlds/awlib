/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_utf_
#define _aw_utf_
#include <aw/common/types.h>
#include <aw/utility/macro.h>
#include <aw/math/math.h>
namespace aw {
namespace unicode {
//! Enumeration of 'special' unicode codepoints
enum class CodePoint : u32 {
	MaxASCII = 0x80,
	SurrogateStart =  0xD800,
	LeadSurrogateStart = 0xD800,
	LeadSurrogateEnd = 0xDBFF,
	TailSurrogateStart = 0xDC00,
	TailSurrogateEnd = 0xDFFF,
	SurrogateEnd = TailSurrogateEnd,
	MaxCodePoint = 0x10FFFF // I hate UTF-16
};

//! Check if code point is a surrogate
inline bool isSurrogate(u16 cp)
{
	return (CodePoint(cp) >= CodePoint::SurrogateStart &&
		CodePoint(cp) <= CodePoint::SurrogateEnd);
}

//! Check if code point is valid
inline bool isValidCodepoint(u32 cp)
{
	return CodePoint(cp) <= CodePoint::MaxCodePoint && !isSurrogate(cp);
}

namespace utf8 {
//! Check whether character is a trail character
inline bool isTrail(u8 ch)
{
	//return (ch & 0b11000000) == 0b10000000;
	return (ch & 0xC0) == 0x80;
}

//! Determine how many characters are in an utf8 sequence
inline size_t sequenceLength(u8 lead) {
	if (lead < 0x80) {
		return 1;
	} else if ((lead >> 5) == 0b110) {
		return 2;
	} else if ((lead >> 4) == 0b1110) {
		return 3;
	} else if ((lead >> 3) == 0b11110) {
		return 4;
#if 0 // non-standard
	} else if ((lead >> 2) == 0b111110) {
		return 5;
	} else if ((lead >> 1) == 0b1111110) {
		return 6;
#endif
	} else {
		return 0;
	}
}

//! Determine how many characters are required to encode codepoint
inline size_t width(u32 cp) {
	if (cp < 0x80) {
		return 1;
	} else if (cp < 0x800) {
		return 2;
	} else if (cp < 0x10000) {
		return 3;
	} else if (cp < 0x10FFFF) {
		return 4;
	}

	return 0;
}

//! Helper to check if encoding is overlong
inline bool isOverlong(u32 cp, size_t length)
{
	return width(cp) != length;
}

/*!
 * Append UTF-8 encoded code point to string
 * (without checking for validity)
 */
template<typename Iterator>
Iterator append_unchecked(u32 cp, Iterator output)
{
	if(cp < 0x80) {
		*(output++) = u8(cp);
	} else if(cp < 0x800) {
		*(output++) = u8((cp >> 6)   | 0xC0);
		*(output++) = u8((cp & 0x3F) | 0x80);
	} else if(cp < 0x10000) {
		*(output++) = u8((cp >> 12)         | 0xE0);
		*(output++) = u8(((cp >> 6) & 0x3F) | 0x80);
		*(output++) = u8((cp & 0x3F)        | 0x80);
	} else {
		*(output++) = u8((cp >> 18)          | 0xF0);
		*(output++) = u8(((cp >> 12) & 0x3F) | 0x80);
		*(output++) = u8(((cp >> 6)  & 0x3F) | 0x80);
		*(output++) = u8((cp & 0x3F)         | 0x80);
	}

	return output;
}

/*!
 * Append UTF-8 encded code point to string, if code point is valid
 */
template<typename Iterator>
Iterator append(u32 cp, Iterator output)
{
	if(isValidCodepoint(cp))
		return append_unchecked(cp, output);

	return output;
}

template<typename Iterator>
Iterator get_unchecked(Iterator iter, Iterator end, u32& cp)
{
	cp = *(input++);
	size_t length = sequenceLength(math::mask8(cp));

	if (length == 1)
		return iter;

	cp = cp & (0x7F >> (length + 1));

	switch (length) {
		case 4:
			cp = (cp << 6) + (*(input++) & 0x3F);
		case 3:
			cp = (cp << 6) + (*(input++) & 0x3F);
		case 2:
			cp = (cp << 6) + (*(input++) & 0x3F);
	}

	return cp;
}

template<typename Iterator>
u32 get(Iterator input, Iterator end, u32& cp)
{
	auto error = [&cp] 
	u32 cp = *(input++);
	size_t length = sequenceLength(math::mask8(cp));

	if (length == 1)
		return cp;

	// Decrement length, because we incremented input by 1
	// so (end - input) is less by one
	--length;
	if (end - input < length) {
		cp = -1;
		return input;
	}

	cp = cp & (0xFF >> (length + 1));

	// There's no perfromance difference between manually unrolled loop
	// and this loop (this loop is even faster, if I can trust my benchmark)
	u8 octet;
	do {
		u8 octet = *(input++);
		if (!isTrail(octet)) {
			cp = -1;
			break;
		}

		cp = (cp << 6) + (octet & 0x3F);
	} while (--length > 0);

	return input;
}


} // namespace utf8

namespace utf16 {
//! Check if code point is first surrogate
inline bool isFirstSurrogate(u16 cp)
{
	return (CodePoint(cp) >= CodePoint::LeadSurrogateStart
		&& CodePoint(cp) <= CodePoint::LeadSurrogateEnd);
}

//! Check if code point is second surrogate
inline bool isSecondSurrogate(u16 cp)
{
	return (CodePoint(cp) >= CodePoint::TailSurrogateStart
		&& CodePoint(cp) <= CodePoint::TailSurrogateEnd);
}

inline size_t width(u32 cp) {
	if(cp < 0x10000) {
		return 1;
	}
	return 2;
}

template<typename Iterator>
inline Iterator append(u32 cp, Iterator output)
{
	if(isValidCodepoint(cp)) {
		if(cp < 0x10000) {
			*(output++) = cp;
		} else {
			cp -= 0x10000;
			*(output++) = 0xDC00 + (cp >> 10);
			*(output++) = 0xDC00 + (cp & 0x3FF);
		}
	}

	return output;
}

template<typename Iterator>
inline u32 get(Iterator& input, Iterator end)
{
	u16 first = *(input++);

	if(!isSurrogate(first)) {
		return first;
	}

	if(isFirstSurrogate(first)) {
		u16 second = *(input++);
		if(isSecondSurrogate(second)) {
			return ((first & 0x3FF) << 10) +
				(second & 0x3FF) + 0x10000;
		}
	} 

	return -1;
}

template<typename Iterator>
inline Iterator append_unchecked(u32 cp, Iterator output)
{
	if(cp < 0x10000) {
		*(output++) = cp;
	} else {
		cp -= 0x10000;
		*(output++) = 0xDC00 + (cp >> 10);
		*(output++) = 0xDC00 + (cp & 0x3FF);
	}

	return output;
}

template<typename Iterator>
inline u32 get_unchecked(Iterator& input, Iterator end)
{
	u16 first = *(input++);

	if(!isSurrogate(first)) {
		return first;
	}
	u16 second = *(input++);

	return ((first & 0x3FF) << 10) + (second & 0x3FF) + 0x10000;
}
} // namespace utf16
} // namespace unicode
} // namespace aw
#endif//_aw_utf_
