#include <aw/meta/pp/foldl.h>

#include "helpers.h"

ASSERT_EQUAL(
	(AW_FOLD_LEFT(AW_IDENTITY, AW_TO_STR, a, b, c)),
	("a", "b", "c")
);

#define SHOW_ASSOC( a, b ) (a b)
ASSERT_EQUAL1(
	AW_FOLDL(SHOW_ASSOC,  1, 2, 3, 4, 5, 6, 7),
	((((((1 2) 3) 4) 5) 6) 7)
);
