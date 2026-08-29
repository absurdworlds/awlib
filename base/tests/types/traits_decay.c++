#include <aw/types/traits/decay.h>
#include <type_traits>

namespace aw {
static_assert(std::is_same_v<decay<int&>, int>);
static_assert(std::is_same_v<decay<int const&>, int>);
static_assert(std::is_same_v<decay<int[4]>, int*>);

static_assert(std::is_same_v<decay_t<int&>, int>);
static_assert(std::is_same_v<decay_t<int const&>, int>);
static_assert(std::is_same_v<decay_t<int[4]>, int*>);
} // namespace aw
