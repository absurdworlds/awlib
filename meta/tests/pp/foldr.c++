#include <aw/meta/pp/foldr.h>

#include <string_view>

using namespace std::string_view_literals;

static_assert(AW_TO_STR(AW_FOLD_RIGHT(AW_IDENTITY, AW_TO_STR, a, b, c)) == R"("a", "b", "c")"sv);
static_assert(AW_TO_STR(AW_FOREACH(AW_TO_STR, a, b, c)) == R"("a", "b", "c")"sv);
