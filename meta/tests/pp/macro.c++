
#include <aw/meta/pp/macro.h>

#include <string_view>

using namespace std::string_view_literals;

static_assert(AW_TO_STR(123) == "123"sv);
static_assert(AW_TO_STR(AW_EXPAND(123)) == "123"sv);
static_assert(AW_TO_STR(AW_APPLY(AW_EXPAND, 123)) == "123"sv);
static_assert(AW_TO_STR(AW_CONCAT(1,23)) == "123"sv);
static_assert(AW_TO_STR(AW_CONCAT3(1,2,3)) == "123"sv);
static_assert(AW_TO_STR(AW_EAT(1,2,3)) == ""sv); // NOLINT: intentional
