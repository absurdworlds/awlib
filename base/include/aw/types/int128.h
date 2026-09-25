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
#if AW_HAS_EXTENSION(int128)
//! \{
//! Alias for compiler-provided 128-bit integer type.
using i128 = __int128;
using u128 = unsigned __int128;
//! \}
#endif
} // namespace aw
#endif //aw_types_int128
