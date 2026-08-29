#include <aw/types/traits/is_container.h>
#include <array>
#include <vector>

namespace aw {
static_assert(is_basic_container_v<std::vector<int>>);
static_assert(is_basic_container_v<std::array<int,3>>);
static_assert(!is_basic_container_v<int>);

static_assert(is_allocator_aware_v<std::vector<int>>);
// std::array keeps its elements inline, and has no allocator
static_assert(!is_allocator_aware_v<std::array<int,3>>);
static_assert(!is_allocator_aware_v<int>);

static_assert(is_allocator_aware_container<std::vector<int>>);
static_assert(!is_allocator_aware_container<std::array<int,3>>);
} // namespace aw
