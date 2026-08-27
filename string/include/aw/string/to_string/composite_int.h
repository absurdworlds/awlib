/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_composite_int_to_string_h
#define aw_composite_int_to_string_h
#include <aw/bit/manip.h>
#include <aw/types/composite_int.h>
#include <aw/string/to_string.h>
#include <aw/string/conv/integer.h>
namespace aw {
template<typename T, typename Formatter = formatter::pretty_print>
std::string to_string(composite_int<T> val, Formatter&& fmt = Formatter{})
{
	using U = make_unsigned<T>;

	composite_int<U> tmp;
	bool sign;

	if (val.sign() < 0) {
		sign = 1;
		tmp = composite_int<U>(-val);
	} else {
		sign = 0;
		tmp = composite_int<U>(val);
	}

	// TODO: figure out a way to specify base
	constexpr size_t base = 10;
	constexpr size_t dg = composite_int<U>::digits;
	size_t lz = tmp.leading_zeros();
	tmp <<= lz;

	radix_accumulator<base, dg> result;
	result.sign = sign;
	for (size_t i = lz; i < dg; ++i) {
		bool carry = bit::top_bit(tmp.high());
		tmp <<= 1;
		result.add_bit(carry);
	}

	return fmt.literal(result.to_string());
}
} // namespace aw
#endif//aw_composite_int_to_string_h
