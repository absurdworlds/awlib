#include <aw/meta/pp/tuple.h>
#include <aw/meta/pp/separators.h>
#include <aw/meta/pp/foldr.h>

#include "helpers.h"

ASSERT_EQUAL1(
	AW_FOLD_RIGHT( AW_COMBINE, AW_IDENTITY, (1), (2), (3), (4), (5), (6), (7) ),
	(1,2,3,4,5,6,7));
