#include <aw/meta/pp/tuple.h>
#include <aw/meta/pp/separators.h>

#include <string_view>

using namespace std::string_view_literals;

static_assert(AW_TO_STR(AW_SEP_SPACE AW_TUPLE(a,b)) == "AW_SEP_SPACE (a,b)"sv);
static_assert(AW_TO_STR(AW_EXPAND( AW_SEP_SPACE AW_TUPLE(a,b) )) == "a b"sv);
static_assert(AW_TO_STR(AW_FIRST( a,b,c )) == "a"sv);
static_assert(AW_TO_STR(AW_SECOND( a,b,c )) == "b"sv);
static_assert(AW_TO_STR(AW_TAIL( a,b,c )) == "b,c"sv);
static_assert(AW_TO_STR(AW_UNPACK( AW_TUPLE(a,b,c) )) == "a,b,c"sv);
static_assert(AW_TO_STR(AW_COMBINE( AW_TUPLE(a,b), AW_TUPLE(c,d)) ) == "(a,b,c,d)"sv);
