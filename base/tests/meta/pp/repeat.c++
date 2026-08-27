#include <aw/meta/pp/macro.h>
#include <aw/meta/pp/repeat.h>

#include <string_view>

using namespace std::string_view_literals;

static_assert(AW_TO_STR(AW_REPEAT(0, ,x)) == ""sv);
static_assert(AW_TO_STR(AW_REPEAT(1, ,x)) == "x"sv);
static_assert(AW_TO_STR(AW_REPEAT(2, ,x)) == "x x"sv);
static_assert(AW_TO_STR(AW_REPEAT(3, ,x)) == "x x x"sv);
static_assert(AW_TO_STR(AW_REPEAT(3, - ,x)) == "x - x - x"sv);
