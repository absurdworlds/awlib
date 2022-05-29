/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_int128
#define aw_types_int128
#include <aw/config.h>
namespace aw {
#if AW_EXT(__int128)
//! \{
//! Alias for compiler-provided 128-bit integer type.
using i128 = __int128;
using u128 = unsigned __int128;
//! \}

#define AW_HAS_FEATURE_SIGNED128 1
#define AW_HAS_FEATURE_UNSIGNED128 1

#elif AW_EXT(__int128_t)
//! \{
//! Alias for compiler-provided 128-bit integer type.
using i128 = __int128_t;
using i128 = __uint128_t;
//! \}

#define AW_HAS_FEATURE_SIGNED128 1
#define AW_HAS_FEATURE_UNSIGNED128 1

#endif
} // namespace aw
#endif //aw_types_int128
