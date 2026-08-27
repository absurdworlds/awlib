/*
 * Copyright (C) 2016-2026 Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_conv_integer_h
#define aw_string_conv_integer_h
#include <aw/string/conv/digits.h>
#include <aw/types/types.h>
#include <string>
namespace aw {
//! Number of bits a single base-\a radix digit is guaranteed to carry
constexpr size_t bits_per_digit(size_t radix)
{
	size_t bits = 0;
	while (radix > 1) {
		radix >>= 1;
		++bits;
	}
	return bits;
}

//! Upper bound on the number of base-\a radix digits in a \a bits-bit integer
template<size_t radix, size_t bits>
constexpr size_t max_digits = bits / bits_per_digit(radix) + 1;

/*!
 * Builds a base-\a R string one bit at a time vid add_bit.
 * Used for extra-wide integers where division is expensive (e.g. composite_int).
 *
 * Based on the "double dabble" algorithm.
 */
template <size_t R, size_t N>
struct radix_accumulator {
	static_assert(R > 1,  "Radix must be at least two.");
	static_assert(R <= 36, "Radix is too big (max. 36).");

	void add_bit(bool const bit)
	{
		size_t i = 0;
		bool carry = bit;
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
