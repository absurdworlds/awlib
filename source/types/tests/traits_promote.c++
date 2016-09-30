#include <aw/types/traits/basic_traits.h>
#include <aw/types/promote.h>

namespace aw {
static_assert(is_same<promote<i8>,  i16>);
static_assert(is_same<promote<i16>, i32>);
static_assert(is_same<promote<i32>, i64>);
#if AW_FEATURE(SIGNED128)
static_assert(is_same<promote<i64>, i128>);
#else
static_assert(!can_promote<i64>);
#endif

static_assert(is_same<promote<u8>,  u16>);
static_assert(is_same<promote<u16>, u32>);
static_assert(is_same<promote<u32>, u64>);
#if AW_FEATURE(SIGNED128)
static_assert(is_same<promote<u64>, u128>);
#else
static_assert(!can_promote<u64>);
#endif
} // namespace aw
