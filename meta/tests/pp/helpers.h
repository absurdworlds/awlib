#ifndef aw_meta_pp_test_helpers_h
#define aw_meta_pp_test_helpers_h

#include <aw/meta/pp/macro.h>

#include <string_view>

using namespace std::string_view_literals;

#define ASSERT_EQUAL(X, Y) static_assert(AW_TO_STR X == AW_TO_SV Y)
#define ASSERT_EQUAL1(X, Y) ASSERT_EQUAL((X),(Y))

#endif // aw_meta_pp_test_helpers_h
