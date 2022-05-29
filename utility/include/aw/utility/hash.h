/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_hash_h
#define aw_utility_hash_h
#include <aw/types/types.h>
#include <aw/types/int128.h>
#include <aw/utility/utility.h>
#include <aw/math/bitmath.h>
#include <array>

namespace aw {
template<typename H>
H hash_combine( H h1, H h2 )
{
	constexpr auto prime32 = 2654435761u;
	constexpr auto prime64 = 1770082059298694101ull;
	constexpr auto digits = std::numeric_limits<H>::digits;
	constexpr auto r = (digits > 32) ? 41 : 19;
	constexpr auto p = (digits > 32) ? prime64 : prime32;

	h1 = math::rotl(h1,r);
	h2 += p;
	h1 ^= (h2 >> 6) + (h2 << 2);
	return h1;
}


using seed128_32 = std::array<u32,4>;
using seed128_64 = std::array<u64,2>;

/*!
 * \{
 * Set of MurmurHash3 hashing algorithms originally written
 * by Austin Appleby.
 *
 * \note
 * Note - The x86 and x64 versions do _not_ produce the same results, as the
 * algorithms are optimized for their respective platforms. You can still
 * compile and run any of them on any platform, but your performance with the
 * non-native version will be less than optimal.
 */

AW_UTILS_EXP
u32 MurmurHash3_x86_32(char const* key,  size_t len, u32 seed);

AW_UTILS_EXP
seed128_32 MurmurHash3_x86_128(char const* key, size_t len, seed128_32 seed);

AW_UTILS_EXP
seed128_64 MurmurHash3_x64_128(char const* key, size_t len, seed128_64 seed);

/* \} */

} // namespace aw
#endif//aw_utility_hash_h
