#include <aw/meta/source_location.h>

#include <string_view>

using namespace std::string_view_literals;

namespace aw {
static_assert(source_location::current().line() == 8);
static_assert(source_location::current().line() == __LINE__);
static_assert(source_location::current().file_name() == std::string_view(__FILE__));

constexpr auto f(source_location loc = source_location::current())
{
	return loc.line();
}

static_assert(f() == 17);
static_assert(f() == 18);
} // namespace aw
