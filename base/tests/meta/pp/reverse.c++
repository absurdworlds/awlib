#include <aw/meta/pp/reverse.h>

#include <string_view>

using namespace std::string_view_literals;

static_assert(AW_TO_STR(AW_REVERSE(a, b, c)) == "c, b, a"sv);
