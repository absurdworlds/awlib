#include <aw/meta/pp/struct.h>

#include <aw/config.h>
#include <string_view>

using namespace std::string_view_literals;

// TODO: strip spaces to eliminate differences in the preprocessor behaviour

static_assert(
    AW_TO_STR(AW_LIST_MEMBER_TYPES(NAME, AW_TUPLE(int, x), AW_TUPLE(int, y))) ==
#if (AW_COMPILER == AW_COMPILER_GCC)
    "int , int"sv
#else
    "int, int"sv
#endif
    );

static_assert(
    AW_TO_STR(AW_DEFINE_STRUCT(s, AW_TUPLE(int, x), AW_TUPLE(int, y))) ==
#if (AW_COMPILER == AW_COMPILER_GCC)
    "struct s { ::aw::type_t<int> x ; ::aw::type_t<int> y ; using tuple_type = std::tuple<int , int >; constexpr operator tuple_type() { return { x , y }; };}"sv
#else
    "struct s { ::aw::type_t<int> x; ::aw::type_t<int> y; using tuple_type = std::tuple<int, int>; constexpr operator tuple_type() { return { x, y }; };}"sv
#endif
    );

AW_DEFINE_STRUCT(s, AW_TUPLE(int, x), AW_TUPLE(int, y));

static_assert(std::is_same_v<s::tuple_type, std::tuple<int, int>>);

void fs()
{
	s s = {
		.x = 1,
		.y = 2,
	};
}
