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
namespace aw::unicode::utf16 {
using char_type   = char16_t;
using string      = std::u16string;

inline constexpr code_point ucs16_max = 0x10000;

//! Check if code point is first surrogate
inline bool is_high_surrogate(char_type cp)
{
	return cp >= surrogate::high_begin && cp <= surrogate::high_end;
}

//! Check if code point is second surrogate
inline bool is_low_surrogate(char_type cp)
{
	return cp >= surrogate::low_begin && cp <= surrogate::low_end;
}

inline size_t width(code_point cp) {
	if (cp < ucs16_max)
		return 1;

	return 2;
}

using decabit = bitword<10, char_type>;

struct codec {
	using char_type   = utf16::char_type;
	using string      = utf16::string;

	template<typename Iterator>
	static Iterator encode(code_point cp, Iterator output)
	{
		if (cp < ucs16_max) {
			*(output++) = cp;
		} else {
			cp -= ucs16_max;
			*(output++) = surrogate::low_begin + decabit::get(cp, 1);
			*(output++) = surrogate::low_begin + decabit::get(cp, 0);
		}

		return output;
	}

	template<typename Iterator>
	static Iterator decode(Iterator input, Iterator end, code_point& cp)
	{
		auto error = [&cp] (Iterator ret) {
			cp = -1;
			return ret;
		};

		char16_t first = *(input++);
		if (is_high_surrogate(first)) {
			if (input == end)
				return error(end);

			char16_t second = *(input++);
			if (!is_low_surrogate(second))
				return error(input);

			cp = decabit::add(0, first);
			cp = decabit::add(cp, second);
			cp += ucs16_max;

			return input;
		}

		// UTF-16 spec doesn't allow reverse order of surrogates
		// even though it can be handled here
		if (is_low_surrogate(first))
			return error(input);

		cp = first;
		return input;
	}
};
} // namespace aw::unicode::utf16
#endif//aw_utility_utf16_h
