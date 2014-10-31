/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_utf_
#define _hrengin_utf_

#include <hrengin/common/macro.h>
#include <hrengin/common/types.h>
#include <hrengin/math/math.h>

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

template<typename char_type, size_t width = sizeof(char_type)>
class UTF;

template<typename char_type>
class UTF<char_type, 1> {
public:
	static bool isTrail(u32 cp)
	{
		return (math::mask8<u32>(cp) & 0xC0) == 0x80;
		//return (math::mask8<u32>(cp) & 0b1100000) == 0b10000000;
	}
	
	static size_t sequenceLength(u8 lead) {
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
	}

	static size_t width(u32 cp) {
		if(cp < 0x80) {
			return 1;
		} else if(cp < 0x800) {
			return 2;
		} else if(cp < 0x10000) {
			return 3;
		}
		return 4;
	}

	static bool isOverlong(u32 cp, size_t length)
	{
		return width(cp) != length;
	}

	template<typename Iterator>
	static Iterator append(u32 cp, Iterator output)
	{
		if(isValidCodepoint(cp)) {
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
				*(output++) = u8(((cp >> 6) & 0x3F)  | 0x80);
				*(output++) = u8((cp & 0x3F)         | 0x80);
			}
		}

		return output;
	}

	template<typename Iterator>
	static u32 get(Iterator& input, Iterator end)
	{
		u32 cp = *(input++);
		size_t length = sequenceLength(math::mask8(cp));
	
		if(length == 1) {
			return cp;
		}

		cp = cp & (0xFF >> (length + 1));

		u8 octet;

		switch(length) {
			case 4:
				if(input == end) {
					return -1;
				}
				octet = *(input++);
				if(!isTrail(octet)) {
					return -1;
				}
				cp = (cp << 6) + (octet & 0x3F);
			case 3:
				if(input == end) {
					return -1;
				}
				octet = *(input++);
				if(!isTrail(octet)) {
					return -1;
				}
				cp = (cp << 6) + (octet & 0x3F);
			case 2:
				if(input == end) {
					return -1;
				}
				octet = *(input++);
				if(!isTrail(octet)) {
					return -1;
				}
				cp = (cp << 6) + (octet & 0x3F);
				break;
			case 0:
				cp = -1;
				break;
		}

		return cp;
	}

	template<typename Iterator>
	static Iterator append_unchecked(u32 cp, Iterator output)
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
			*(output++) = u8(((cp >> 6) & 0x3F)  | 0x80);
			*(output++) = u8((cp & 0x3F)         | 0x80);
		}

		return output;
	}

	template<typename Iterator>
	static u32 get_unchecked(Iterator& input, Iterator end)
	{
		u32 cp = *(input++);
		size_t length = sequenceLength(math::mask8(cp));
	
		if(length == 1) {
			return cp;
		}

		cp = cp & (0x7F >> (length + 1));

		switch(length) {
			case 4:
				cp = (cp << 6) + (*(input++) & 0x3F);
			case 3:
				cp = (cp << 6) + (*(input++) & 0x3F);
			case 2:
				cp = (cp << 6) + (*(input++) & 0x3F);
		}

		return cp;
	}
};

template<typename char_type>
class UTF<char_type, 2> {
public:
	//! Check if code point is first surrogate
	static bool isFirstSurrogate(u16 cp)
	{
		return (CodePoint(cp) >= CodePoint::LeadSurrogateStart
			&& CodePoint(cp) <= CodePoint::LeadSurrogateEnd);
	}

	//! Check if code point is second surrogate
	static bool isSecondSurrogate(u16 cp)
	{
		return (CodePoint(cp) >= CodePoint::TailSurrogateStart
			&& CodePoint(cp) <= CodePoint::TailSurrogateEnd);
	}

	static size_t width(u32 cp) {
		if(cp < 0x10000) {
			return 1;
		}
		return 2;
	}

	template<typename Iterator>
	static Iterator append(u32 cp, Iterator output)
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
	static u32 get(Iterator& input, Iterator end)
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
	static Iterator append_unchecked(u32 cp, Iterator output)
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
	static u32 get_unchecked(Iterator& input, Iterator end)
	{
		u16 first = *(input++);

		if(!isSurrogate(first)) {
			return first;
		}
		u16 second = *(input++);

		return ((first & 0x3FF) << 10) + (second & 0x3FF) + 0x10000;
	}
};

template<typename char_type>
class UTF<char_type, 4> {
public:
	static size_t width(u32 cp) {
		return 1;
	}

	template<typename Iterator>
	static Iterator append(u32 cp, Iterator output)
	{
		if(isValidCodepoint(cp)) {
			*(output++) = cp;
		}

		return output;
	}

	template<typename Iterator>
	static u32 get(Iterator& input, Iterator end)
	{
		u32 cp = *(input++);

		if(!isValidCodepoint(cp)) {
			return -1;
		}

		return cp;
	}

	template<typename Iterator>
	static Iterator append_unchecked(u32 cp, Iterator output)
	{
		*(output++) = cp;

		return output;
	}

	template<typename Iterator>
	static u32 get_unchecked(Iterator& input, Iterator end)
	{
		return *(input++);
	}
};

} // namespace locale
} // namespace hrengin
#endif//_hrengin_utf_
