
#include <aw/meta/pp/macro.h>
#include <aw/meta/pp/separators.h>

#include "helpers.h"

ASSERT_EQUAL1(123, 123);
ASSERT_EQUAL1(AW_TO_STR(123), "123");
ASSERT_EQUAL1(AW_EXPAND(123), 123);
ASSERT_EQUAL1(AW_APPLY(AW_EXPAND, 123), 123);
ASSERT_EQUAL1(AW_CONCAT(1,23), 123);
ASSERT_EQUAL1(AW_CONCAT3(1,2,3), 123);
ASSERT_EQUAL1(AW_EAT(1,2,3), );  // NOLINT: intentional
// NOTE: these macros get expanded by passing them to ASSERT_EQUAL1
// so while this test is correct, it doens't quite do what's intended
ASSERT_EQUAL1(
	AW_APPLY(AW_SEP_SPACE AW_DEFER, (a, b)),
	AW_SEP_SPACE (a, b));
ASSERT_EQUAL1(
	AW_EXPAND(AW_APPLY(AW_SEP_SPACE AW_DEFER, (a, b))),
	a b);
