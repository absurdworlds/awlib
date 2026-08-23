#include "aw/types/promote.h"

#include "aw/types/traits/basic_traits.h"

namespace aw {
static_assert(is_same_v<promote<i8>,  i16>);
static_assert(is_same_v<promote<i16>, i32>);
static_assert(is_same_v<promote<i32>, i64>);
#if AW_FEATURE(SIGNED128)
static_assert(is_same_v<promote<i64>, i128>);
#else
static_assert(!can_promote<i64>);
#endif

static_assert(is_same_v<promote<u8>,  u16>);
static_assert(is_same_v<promote<u16>, u32>);
static_assert(is_same_v<promote<u32>, u64>);
#if AW_FEATURE(SIGNED128)
static_assert(is_same_v<promote<u64>, u128>);
#else
static_assert(!can_promote<u64>);
#endif
} // namespace aw
