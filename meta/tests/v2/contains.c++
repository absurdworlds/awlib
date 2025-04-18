#include <aw/meta/v2/contains.h>
#include <aw/meta/list.h>
#include <tuple>

namespace aw::meta {

static_assert( !contains_v<int, list<float, double>> );
static_assert(  contains_v<int, list<float, double, int>> );

static_assert( !contains_v<int, std::tuple<float, list<bool, char>, double>> );
static_assert(  contains_v<int, std::tuple<float, list<bool, char>, double, int>> );

} // namespace aw::meta
