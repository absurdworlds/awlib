#include <aw/meta/pp/foldr.h>
#include <aw/meta/pp/separators.h>

#include <aw/config.h>

#include "helpers.h"

ASSERT_EQUAL1(AW_N_ARGS((,),(,),(,)), 3);

ASSERT_EQUAL(
	(AW_FOLD_RIGHT(AW_IDENTITY, AW_TO_STR, a, b, c)),
	("a", "b", "c"));

#if AW_COMPILER == AW_COMPILER_GCC
ASSERT_EQUAL(
	(AW_FOLD_RIGHT(AW_SEP_SEMI, AW_SEP_SPACE AW_DEFER, (int,a), (float,b), (char,c) );),
	(int a ; float b ; char c ;)
);
#else
ASSERT_EQUAL(
	(AW_FOLD_RIGHT(AW_SEP_SEMI, AW_SEP_SPACE AW_DEFER, (int,a), (float,b), (char,c) );),
	(int a; float b; char c;)
);
#endif

ASSERT_EQUAL(
	(AW_FOREACH(AW_TO_STR, a, b, c)),
	("a", "b", "c"));

#define SHOW_ASSOC( a, b ) (a b)

ASSERT_EQUAL1(
	AW_FOLDR(SHOW_ASSOC,  1, 2, 3, 4, 5, 6, 7),
	(1 (2 (3 (4 (5 (6 7))))))
);
