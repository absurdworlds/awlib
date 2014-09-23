/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_utf_
#define _hrengin_utf_

#include <type_traits>

#include <hrengin/common/macro.h>
#include <hrengin/common/types.h>
#include <hrengin/common/math.h>

namespace hrengin {
namespace locale {

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

//! Check if code point is first surrogate
inline bool isFirstSurrogate(u16 cp)
{
	return (CodePoint(cp) >= CodePoint::LeadSurrogateStart
		&& CodePoint(cp) <= CodePoint::LeadSurrogateEnd);
}

//! Check if code point is second surrogate
inline bool isFirstSurrogate(u16 cp)
{
	return (CodePoint(cp) >= CodePoint::TailSurrogateStart
		&& CodePoint(cp) <= CodePoint::TailSurrogateEnd);
}

//! Check if code point is a surrogate
inline bool isSurrogate(u16 cp)
{
	return (CodePoint(cp) >= CodePoint::SurrogateStart
		&& CodePoint(cp) <= CodePoint::SurrogateEnd);
}

//! Check if code point is valid
inline bool isValidCodepoint(u32 cp)
{
	return (CodePoint(cp) <= CodePoint::MaxCodePoint 
		&& !isSurrogate(cp));
}

namespace utf8 {
inline bool isTrail(u32 cp)
{
	return (math::mask8<u32>(cp) & 0xC0) == 0x80;
	//return (math::mask8<u32>(cp) & 0b1100000) == 0b10000000;
}

inline size_t width(u32 cp) {
	if(cp < 0x80) {
		return 1;
	} else if(cp < 0x800) {
		return 2;
	} else if(cp < 0x10000) {
		return 3;
	}
	return 4;
}

inline bool isOverlong(u32 cp, size_t length)
{
	return width(cp) != length;
}

inline size_t sequenceLength(u8 lead) {
	if(lead < 0x80) {
		return 1;
	} else if((lead >> 5) == 0x6) {
		return 2;
	} else if((lead >> 4) == 0xE) {
		return 3;
	} else if((lead >> 3) == 0x1E) {
		return 4;
	} else {
		return 0;
	}
#if 0
	else if((lead >> 2) == 0x3E) {
		return 5;
	} else if((lead >> 2) == 0x7E) {
		return 6;
	}
#endif
}

template<typename Iterator>
static Iterator append(u32 cp, Iterator output)
{
	if(isValidCodepoint(cp)) {
		if(value < 0x80) {
			*(output++) = u8(cp);
		} else if(value < 0x800) {
			*(output++) = u8((cp >> 6)   | 0xC0);
			*(output++) = u8((cp & 0x3F) | 0x80);
		} else if(cp < 0x10000)) {
			*(output++) = u8((cp >> 12)         | 0xE0);
			*(output++) = u8(((cp >> 6) & 0x3F) | 0x80);
			*(output++) = u8((cp & 0x3F)        | 0x80);
		} else {
			*(output++) = u8((cp >> 18)          | 0xF0);
			*(output++) = u8(((cp >> 12) & 0x3F) | 0x80);
			*(output++) = u8(((cp >> 6) & 0x3F)  | 0x80);
			*(output++) = u8((cp & 0x3F)         | 0x80);
		}
	}

	return output;
}

template<typename Iterator>
static u32 get(Iterator& input, Iterator end)
{
	u32 cp;
	size_t length = sequenceLength(input);

	switch(length) {
		default:
		case 0:
			cp = -1;
			break;
		case 1:
			cp = *input;
			break;
		case 2:
			cp = *input << 6 & 0x7FF;
			++input;
			cp += *(input) & 0x3F;
			break;
		case 3:
			cp = *input << 12 & 0xFFFF;
			++input;
			cp += *(input) << 6 & 0xFFF;
			++input;
			cp += *(input) & 0x3F;
			break;
		case 4:
			cp = *input << 18 & 0x1FFFFF;
			++input;
			cp += *(input) << 12 & 0x3FFFF;
			++input;
			cp += *(input) << 6 & 0xFFF;
			++input;
			cp += *(input) & 0x3F;
			break;
		}
	}

	return cp;
}

} // namespace utf8
} // namespace locale
} // namespace hrengin

#endif//_hrengin_utf_
