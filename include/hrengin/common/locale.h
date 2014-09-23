/*
   This file is a part of boost library, apart from the fact that it was
   reformatted to match hrengin conventions.
 */
/*
   Copyright (c) 2012 Artyom Beilis (Tonkikh)
   
   Distributed under the Boost Software License, Version 1.0. (See
   accompanying file BOOST_LICENSE_1_0.txt or copy at
   http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef _hrengin_locale_
#define _hrengin_locale_

#include <hrengin/common/macro.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace locale {

typedef u32 code_point;

static const code_point illegal = 0xFFFFFFFF;

static const code_point incomplete = 0xFFFFFFFE;

inline bool isValidCodepoint(code_point v)
{
	if(v > 0x10FFFF) {
		return false;
	}

	// surrogates
	if(0xD800 <= v && v <= 0xDFFF) {
		return false;
	}

	return true;
}

template<typename CharType, int size = sizeof(CharType)>
struct utf_traits;

template<typename CharType>
struct utf_traits<CharType,1> {

	typedef CharType char_type;

	static int trail_length(char_type ci) 
	{
		unsigned char c = ci;
		if(c < 128) {
			return 0;
		}
		if(BRANCH_UNLIKELY(c < 194)) {
			return -1;
		}
		if(c < 224) {
			return 1;
		}
		if(c < 240) {
			return 2;
		}
		if(BRANCH_LIKELY(c <= 244)) {
			return 3;
		}
		return -1;
	}

	static const int max_width = 4;

	static int width(code_point value)
	{
		if(value <= 0x7F) {
			return 1;
		} else if(value <= 0x7FF) {
			return 2;
		} else if(BRANCH_LIKELY(value <= 0xFFFF)) {
			return 3;
		} else {
			return 4;
		}
	}

	static bool is_trail(char_type ci)
	{
		unsigned char c = ci;
		return (c & 0xC0) == 0x80;
	}

	static bool is_lead(char_type ci)
	{
		return !is_trail(ci);
	}

	template<typename Iterator>
	static code_point decode(Iterator &p, Iterator e)
	{
		if(BRANCH_UNLIKELY(p == e)) {
			return incomplete;
		}

		unsigned char lead = *p++;

		// First byte is fully validated here
		int trail_size = trail_length(lead);

		if(BRANCH_UNLIKELY(trail_size < 0))
			return illegal;

		//
		// Ok as only ASCII may be of size = 0
		// also optimize for ASCII text
		//
		if(trail_size == 0) {
			return lead;
		}
			
		code_point c = lead & ((1<<(6-trail_size))-1);

		// Read the rest
		unsigned char tmp;
		switch(trail_size) {
		case 3:
			if(BRANCH_UNLIKELY(p==e)) {
				return incomplete;
			}
			tmp = *p++;
			if (!is_trail(tmp)) {
				return illegal;
			}
			c = (c << 6) | ( tmp & 0x3F);
		case 2:
			if(BRANCH_UNLIKELY(p==e)) {
				return incomplete;
			}
			tmp = *p++;
			if (!is_trail(tmp)) {
				return illegal;
			}
			c = (c << 6) | ( tmp & 0x3F);
		case 1:
			if(BRANCH_UNLIKELY(p==e)) {
				return incomplete;
			}
			tmp = *p++;
			if (!is_trail(tmp)) {
				return illegal;
			}
			c = (c << 6) | ( tmp & 0x3F);
		}

		// Check code point validity: no surrogates and valid range
		if(BRANCH_UNLIKELY(!isValidCodepoint(c))) {
			return illegal;
		}

		// make sure it is the most compact representation
		if(BRANCH_UNLIKELY(width(c) != trail_size + 1)) {
			return illegal;
		}

		return c;
	}

	template<typename Iterator>
	static code_point decode_valid(Iterator &p)
	{
		unsigned char lead = *p++;
		if(lead < 192) {
			return lead;
		}

		int trail_size;

		if(lead < 224) {
			trail_size = 1;
		} else if(BRANCH_LIKELY(lead < 240)) {
			trail_size = 2;
		} else {
			trail_size = 3;
		}

		code_point c = lead & ((1<<(6-trail_size))-1);

		switch(trail_size) {
		case 3:
			c = (c << 6) | ( static_cast<u8>(*p++) & 0x3F);
		case 2:
			c = (c << 6) | ( static_cast<u8>(*p++) & 0x3F);
		case 1:
			c = (c << 6) | ( static_cast<u8>(*p++) & 0x3F);
		}

		return c;
	}


	template<typename Iterator>
	static Iterator encode(code_point value, Iterator out)
	{
		if(value <= 0x7F) {
			*out++ = static_cast<char_type>(value);
		} else if(value <= 0x7FF) {
			*out++ = static_cast<char_type>((value >> 6) | 0xC0);
			*out++ = static_cast<char_type>((value & 0x3F) | 0x80);
		} else if(BRANCH_LIKELY(value <= 0xFFFF)) {
			*out++ = static_cast<char_type>((value >> 12) | 0xE0);
			*out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
			*out++ = static_cast<char_type>((value & 0x3F) | 0x80);
		} else {
			*out++ = static_cast<char_type>((value >> 18) | 0xF0);
			*out++ = static_cast<char_type>(((value >> 12) & 0x3F) | 0x80);
			*out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
			*out++ = static_cast<char_type>((value & 0x3F) | 0x80);
		}
		return out;
	}
}; // utf8

template<typename CharType>
struct utf_traits<CharType,2> {
	typedef CharType char_type;

	// See RFC 2781
	static bool is_first_surrogate(u16 x)
	{
		return 0xD800 <= x && x <= 0xDBFF;
	}
	static bool is_second_surrogate(u16 x)
	{
		return 0xDC00 <= x && x <= 0xDFFF;
	}
	static code_point combine_surrogate(u16 w1,u16 w2)
	{
		return ((code_point(w1 & 0x3FF) << 10) | (w2 & 0x3FF)) + 0x10000;
	}
	static int trail_length(char_type c)
	{
		if(is_first_surrogate(c)) {
			return 1;
		}
		if(is_second_surrogate(c)) {
			return -1;
		}
		return 0;
	}
	static bool is_trail(char_type c)
	{
		return is_second_surrogate(c);
	}
	static bool is_lead(char_type c)
	{
		return !is_second_surrogate(c);
	}

	template<typename It>
	static code_point decode(It &current, It last)
	{
		if(BRANCH_UNLIKELY(current == last)) {
			return incomplete;
		}
		u16 w1 = *current++;
		if(BRANCH_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
			return w1;
		}
		if(w1 > 0xDBFF) {
			return illegal;
		}
		if(current==last) {
			return incomplete;
		}
		u16 w2 = *current++;
		if(w2 < 0xDC00 || 0xDFFF < w2) {
			return illegal;
		}
		return combine_surrogate(w1,w2);
	}
	template<typename It>
	static code_point decode_valid(It &current)
	{
		u16 w1=*current++;
		if(BRANCH_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
			return w1;
		}
		u16 w2=*current++;
		return combine_surrogate(w1,w2);
	}

	static const int max_width = 2;
	static int width(code_point u)
	{
		return u>=0x10000 ? 2 : 1;
	}

	template<typename It>
	static It encode(code_point u, It out)
	{
		if(BRANCH_LIKELY(u<=0xFFFF)) {
			*out++ = static_cast<char_type>(u);
		} else {
			u -= 0x10000;
			*out++ = static_cast<char_type>(0xD800 | (u>>10));
			*out++ = static_cast<char_type>(0xDC00 | (u & 0x3FF));
		}
		return out;
	}
}; // utf16;


template<typename CharType>
struct utf_traits<CharType,4> {
	typedef CharType char_type;
	static int trail_length(char_type c)
	{
		if(isValidCodepoint(c)) {
			return 0;
		}
		return -1;
	}
	static bool is_trail(char_type /*c*/)
	{
		return false;
	}
	static bool is_lead(char_type /*c*/)
	{
		return true;
	}

	template<typename It>
	static code_point decode_valid(It &current)
	{
		return *current++;
	}

	template<typename It>
	static code_point decode(It &current, It last)
	{
		if(BRANCH_UNLIKELY(current == last)) {
			return incomplete;
		}
		code_point c = *current++;
		if(BRANCH_UNLIKELY(!isValidCodepoint(c))) {
			return illegal;
		}
		return c;
	}
	static const int max_width = 1;
	static int width(code_point /*u*/)
	{
		return 1;
	}
	template<typename It>
	static It encode(code_point u, It out)
	{
		*out++ = static_cast<char_type>(u);
		return out;
	}

}; // utf32

} // namespace locale
} // namespace hrengin

#endif//_hrengin_locale_
