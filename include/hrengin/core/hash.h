/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hash_
#define _hrengin_hash_
#include <hrengin/common/types.h>
#include <hrengin/core/core.h>

namespace hrengin {
/*!
 * Helper union to hold 128-bit values
 */
union u128 {
	u64 as64[2];
	u32 as32[4];
};

//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.
//-----------------------------------------------------------------------------
// Note - The x86 and x64 versions do _not_ produce the same results, as the
// algorithms are optimized for their respective platforms. You can still
// compile and run any of them on any platform, but your performance with the
// non-native version will be less than optimal.

HR_CORE_EXP
void MurmurHash3_x86_32  (void const * key, size_t len, u32 seed, void * out);

HR_CORE_EXP
void MurmurHash3_x86_128 (void const * key, size_t len, u128 seed, void * out);

HR_CORE_EXP
void MurmurHash3_x64_128 (void const * key, size_t len, u128 seed, void * out);

} // namespace hrengin
#endif//_hrengin_hash_
