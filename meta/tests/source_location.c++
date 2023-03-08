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

#if (AW_COMPILER == AW_COMPILER_CLANG && AW_COMPILER_VERSION_MAJOR == 15)
#warning "std::source_location is broken in clang 15"
#else
static_assert(f() == 20);
static_assert(f() == 21);
static_assert(f() == __LINE__);
#endif
} // namespace aw
