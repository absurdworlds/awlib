/*
 * Copyright (C) 2014-2026 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_bit_count_h
#define aw_bit_count_h
#include <aw/config.h>
#include <aw/types/types.h>
#if !AW_EXT(__builtin_clzll) || !AW_EXT(__builtin_ctzll)
#include <aw/bit/manip.h>
#endif
namespace aw::bit {
inline size_t leading_zeros(u32 x)
{
	size_t n = 0;

#if AW_EXT(__builtin_clz)
	if (x != 0)
		n = __builtin_clz(x);
	else
		n = 32;
#else
	if (x == 0)
		return 32;

	if (x <= 0x0000ffff) {
		n +=  16;
		x <<= 16;
	}
	if (x <= 0x00ffffff) {
		n +=  8;
		x <<= 8;
	}
	if (x <= 0x0fffffff) {
		n +=  4;
		x <<= 4;
	}
	if (x <= 0x3fffffff) {
		n +=  2;
		x <<= 2;
	}

	n += (x <= 0x7fffffff);
#endif

	return n;
}

inline size_t leading_zeros(u64 x)
{
	size_t n = 0;
#if AW_EXT(__builtin_clzll)
	if (x != 0)
		n = __builtin_clzll(x);
	else
		n = 64;
#else
	if (x <= 0x00000000'ffffffff) {
		n +=  32;
		n += leading_zeros(u32(lower_half(x)));
	} else {
		n += leading_zeros(u32(upper_half(x)));
	}
#endif

	return n;
}


inline size_t trailing_zeros(u32 x)
{
	size_t n = 0;

#if AW_EXT(__builtin_ctz)
	if (x != 0)
		n = __builtin_ctz(x);
	else
		n = 32;
#else
	if (x == 0)
		return 32;

	if (x & 0x1)
		return 0;

	if ((x & 0xffff) == 0) {
		x >>= 16;
		n  += 16;
	}
	if ((x & 0xff) == 0) {
		x >>= 8;
		n  += 8;
	}
	if ((x & 0xf) == 0) {
		x >>= 4;
		n  += 4;
	}
	if ((x & 0x3) == 0) {
		x >>= 2;
		n  += 2;
	}

	n += !(x & 0x1);
#endif

	return n;
}

inline size_t trailing_zeros(u64 x)
{
	size_t n = 0;

#if AW_EXT(__builtin_ctzll)
	if (x != 0)
		n = __builtin_ctzll(x);
	else
		n = 64;
#else
	if (x & 0x1)
		return 0;

	if ((x & 0xffffffff) == 0) {
		n  += 32;

		n += trailing_zeros(u32(upper_half(x)));
	} else {
		n += trailing_zeros(u32(lower_half(x)));
	}
#endif

	return n;
}

//! Alias for leading_zeros()
template <typename T>
size_t clz(T value)
{
	return leading_zeros(value);
}

//! Alias for trailing_zeros()
template <typename T>
size_t ctz(T value)
{
	return trailing_zeros(value);
}
} // namespace aw::bit
#endif//aw_bit_count_h
