#include <aw/meta/pp/struct.h>

#include <aw/config.h>

#include "helpers.h"

// TODO: strip spaces to eliminate differences in the preprocessor behaviour

#if AW_COMPILER == AW_COMPILER_GCC
ASSERT_EQUAL(
	(AW_LIST_MEMBER_TYPES(NAME, AW_TUPLE(int, x), AW_TUPLE(int, y))),
	(int , int)
);
#else
ASSERT_EQUAL(
	(AW_LIST_MEMBER_TYPES(NAME, AW_TUPLE(int, x), AW_TUPLE(int, y))),
	(int, int)
);
#endif

#if AW_COMPILER == AW_COMPILER_GCC
ASSERT_EQUAL(
	(AW_DEFINE_STRUCT(s, AW_TUPLE(int, x), AW_TUPLE(int, y))),
	(struct s {
		::aw::type_t<int> x ;
		::aw::type_t<int> y ;
		using tuple_type = std::tuple<int , int >;
		constexpr operator tuple_type() { return { x , y }; }
	})
);
#else
ASSERT_EQUAL(
	(AW_DEFINE_STRUCT(s, AW_TUPLE(int, x), AW_TUPLE(int, y))),
	(struct s {
		::aw::type_t<int> x;
		::aw::type_t<int> y;
		using tuple_type = std::tuple<int, int>;
		constexpr operator tuple_type() { return { x, y }; }
	})
);
#endif

#if AW_COMPILER == AW_COMPILER_GCC
ASSERT_EQUAL(
	(AW_DEFINE_STRUCT( str, (int, x), (int, y) )),
	(struct str {
		::aw::type_t<int> x ;
		::aw::type_t<int> y ;
		using tuple_type = std::tuple<int , int >;
		constexpr operator tuple_type() { return { x , y }; }
	})
);
#else
ASSERT_EQUAL(
	(AW_DEFINE_STRUCT( str, (int, x), (int, y) )),
	(struct str {
		::aw::type_t<int> x;
		::aw::type_t<int> y;
		using tuple_type = std::tuple<int, int>;
		constexpr operator tuple_type() { return { x, y }; }
	})
);
#endif

AW_DEFINE_STRUCT(s, AW_TUPLE(int, x), AW_TUPLE(int, y));

static_assert(std::is_same_v<s::tuple_type, std::tuple<int, int>>);

void fs()
{
	s s = {
		.x = 1,
		.y = 2,
	};
}
