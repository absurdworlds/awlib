/*
 * Copyright (C) 2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_conv_integer_h
#define aw_string_conv_integer_h
#include <aw/utility/string/conv/digits.h>
namespace aw {
/*!
 * TODO: better name
 */
template <size_t R, size_t N>
struct int_converter {
	static_assert(R > 1,  "Radix must be at least two.");
	static_assert(R < 36, "Radix is too big (max. 36).");

	void add_digit(bool carry)
	{
		size_t i = 0;
		do {
			auto& digit = digits[i];
			digit *= 2;
			digit += carry;
			carry = digit > (R - 1);
			if (carry)
				digit -= R;
		} while (i++ < top_digit);

		if (carry)
			++digits[++top_digit];
	}

	std::string to_string()
	{
		std::string tmp;
		tmp.reserve(top_digit + 2);
		if (sign)
			tmp += '-';
		for (size_t i = 0; i <= top_digit; ++i)
			tmp += digit_chars[digits[top_digit - i]];
		return tmp;
	}

	bool sign = 0;
	size_t top_digit = 0;
	u8 digits[N] = {};
};
} // namespace aw
#endif//aw_string_conv_integer_h
