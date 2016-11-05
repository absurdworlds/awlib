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
	constexpr auto& upper    = math::upper_half<U>;
	constexpr auto& lower    = math::lower_half<U>;
	constexpr auto& to_upper = math::lower_to_upper<U>;

	// Split integers into lower and upper halves
	U ah = upper(a);
	U al = lower(a);
	U bh = upper(b);
	U bl = lower(b);

	// Multiply halves together
	U ah_bh = ah * bh;
	U ah_bl = ah * bl;
	U al_bh = al * bh;
	U al_bl = al * bl;

	// Compute middle bits
	U mid_lo = lower(ah_bl) + lower(al_bh);
	U mid_hi = upper(ah_bl) + upper(al_bh);

	// Compute carry bit
	U carry = upper(mid_lo + upper(al_bl));

	// Add all the bits together
	U hi = ah_bh + mid_hi + carry;
	U lo = al_bl + to_upper(mid_lo);

	return {T(hi), lo};
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
