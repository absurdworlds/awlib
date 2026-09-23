/*
 * Copyright (C) 2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_composite_int_h
static_assert(false, "Do not include this file directly");
#endif

namespace aw {
template<typename T>
auto composite_int<T>::mul(U a, U b) -> composite_int<T>
{
	constexpr auto& upper    = bit::upper_half<U>;
	constexpr auto& lower    = bit::lower_half<U>;
	constexpr auto& to_upper = bit::lower_to_upper<U>;

	// Split integers into lower and upper halves
	U const ah = upper(a);
	U const al = lower(a);
	U const bh = upper(b);
	U const bl = lower(b);

	// Multiply halves together
	U const ah_bh = ah * bh;
	U const ah_bl = ah * bl;
	U const al_bh = al * bh;
	U const al_bl = al * bl;

	// Compute middle bits
	U const mid_lo = lower(ah_bl) + lower(al_bh);
	U const mid_hi = upper(ah_bl) + upper(al_bh);

	// Compute carry bit
	U const carry = upper(mid_lo + upper(al_bl));

	// Add all the bits together
	U const hi = ah_bh + mid_hi + carry;
	U const lo = al_bl + to_upper(mid_lo);

	return {T(hi), lo};
}

namespace _impl {
template<typename T>
auto div(composite_int<T> const& a, composite_int<T> const& b)
        -> enable_if<is_signed<T>, std::pair<composite_int<T>, composite_int<T>>>
{
	using U = make_unsigned<T>;

	bool const q_sign = (a.high() < 0) != (b.high() < 0);
	bool const r_sign = (b.high() < 0);

	auto const aa = a.high() < 0 ? composite_int<U>(-a) : composite_int<U>(a);
	auto const bb = b.high() < 0 ? composite_int<U>(-b) : composite_int<U>(b);

	auto const result = composite_int<U>::div(aa, bb);

	auto const& quot = result.first;
	auto const& rem  = result.second;

	return {q_sign ? composite_int<T>(-quot) : composite_int<T>(quot),
	        r_sign ? composite_int<T>(-rem)  : composite_int<T>(rem)};
}

template<typename T>
auto div(composite_int<T> const& a, composite_int<T> const& b)
        -> enable_if<is_unsigned<T>,  std::pair<composite_int<T>, composite_int<T>>>
{
	size_t const lza = a.leading_zeros();
	size_t const lzb = b.leading_zeros();
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
