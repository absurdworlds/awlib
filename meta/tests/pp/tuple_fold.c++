#include <aw/meta/pp/tuple.h>
#include <aw/meta/pp/separators.h>
#include <aw/meta/pp/foldr.h>

#include <string_view>

using namespace std::string_view_literals;

static_assert(
	AW_TO_STR(AW_FOLD_RIGHT( AW_COMBINE, AW_IDENTITY, (1), (2), (3), (4), (5), (6), (7) )) ==
	"(1,2,3,4,5,6,7)"sv);
