/*
 * Copyright (C) 2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/string/conv/integer.h>
namespace aw {
template<typename T>
std::string as_string(composite_int<T> val)
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

	return result.to_string();
}

namespace _impl {
template<typename T>
auto div(composite_int<T> const& a, composite_int<T> const& b)
        -> enable_if<is_signed<T>, std::pair<composite_int<T>, composite_int<T>>>
{
	using U = make_unsigned<T>;

	bool q_sign = (a.high_part() < 0) != (b.high_part() < 0);
	bool r_sign = (b.high_part() < 0);

	auto aa = a.high_part() < 0 ? -a : a;
	auto bb = b.high_part() < 0 ? -b : b;

	auto result = composite_int<U>::div(aa, bb);

	auto& quot = result.first;
	auto& rem  = result.second;

	return {q_sign ? -quot : composite_int<T>(quot),
	        r_sign ? -rem  : composite_int<T>(rem)};
}

template<typename T>
auto div(composite_int<T> const& a, composite_int<T> const& b)
        -> enable_if<is_unsigned<T>,  std::pair<composite_int<T>, composite_int<T>>>
{
	size_t lza = a.leading_zeros();
	size_t lzb = b.leading_zeros();
	if (lzb < lza)
		return {}; // 1 / 2 == 0

	size_t diff = lzb - lza;

	composite_int<T> dividend = a;
	composite_int<T> result {};
	composite_int<T> rem = b << diff;

	do {
		result <<= 1;
		if (dividend > rem) {
			dividend -= rem;
			result |= 1;
		}

		rem >>= 1;
	} while (diff --> 0);

	return {result, rem};
}
} // namespace _impl

template<typename T>
auto composite_int<T>::div(composite_int const& a, composite_int const& b)
        -> std::pair<composite_int, composite_int>
{
	return _impl::div(a, b);
}
} // namespace aw
