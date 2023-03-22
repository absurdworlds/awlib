/*
 * Copyright (C) 2014-2023  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_utf32_h
#define aw_utility_utf32_h
#include <aw/utility/unicode/unicode.h>
namespace aw::unicode {
namespace utf32 {
using char_type   = char32_t;
using string      = std::u32string;

struct codec {
	using char_type   = utf32::char_type;
	using string      = utf32::string;

	template<typename Iterator>
	static Iterator encode(code_point cp, Iterator output)
	{
		*(output++) = cp;
		return output;
	}

	template<typename Iterator>
	static Iterator decode(Iterator input, Iterator end, code_point& cp)
	{
		if (input != end) {
			cp = *(input++);
			return input;
		}
		cp = -1;
		return end;
	}
};
} // namespace utf32
} // namespace aw::unicode
#endif//aw_utility_utf32_h
