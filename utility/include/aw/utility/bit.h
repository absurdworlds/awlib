/*
 * Copyright (C) 2023 Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_bit_h
#define aw_utility_bit_h

#include <aw/types/types.h>

#include <limits>

// TODO: replace bitmath.h with this header

namespace aw {

/*!
 * Mask of lower N bits.
 */
template <size_t N, typename Int = size_t>
inline constexpr Int mask =
	N >= std::numeric_limits<Int>::digits ?
		~Int(0u) :
		(Int(1u) << N) - 1u;

} // namespace aw

#endif // aw_utility_bit_h
