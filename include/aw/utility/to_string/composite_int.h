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
#include <aw/types/composite_int.h>
#include <aw/utility/to_string.h>
#include <aw/utility/to_string/formatters/integer.h>
namespace aw {
template<typename T, typename Formatter>
std::string to_string(composite_int<T> val, Formatter&& fmt = Formatter{})
{
	using U = make_unsigned<T>;

	composite_int<U> tmp;
	bool sign;

	if (val.sign() < 0) {
		sign = 1;
		tmp = -val;
	} else {
		sign = 0;
		tmp = val;
	}

	// TODO: figure out a way to specify base
	constexpr size_t base = 10;
	constexpr size_t dg = composite_int<U>::digits;
	size_t lz = tmp.leading_zeros();
	tmp <<= lz;

	constexpr size_t size_needed = composite_int<T>::digits / math::log2(base) + 1;

	int_converter<base, size_needed> result;
	result.sign = sign;
	for (size_t i = lz; i < dg; ++i) {
		bool carry = math::top_bit(tmp.high_part());
		tmp <<= 1;
		result.add_digit(carry);
	}

	return fmt.literal(result.to_string());
}
} // namespace aw
#endif//aw_composite_int_to_string_h
