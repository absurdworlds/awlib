#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/is_iterable.h>
#include <vector>

namespace aw {
static_assert(is_iterable<int[10]>);
static_assert(is_const_iterable<int[10]>);

static_assert(is_iterable<std::vector<int>>);
static_assert(is_const_iterable<std::vector<int>>);

static_assert(!is_iterable<int>);
static_assert(!is_const_iterable<int>);
} // namespace aw
