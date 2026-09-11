
#include <aw/assert.h>

// A disabled assertion must not instantiate its body.
// This type has no formatter, so the file only compiles if the body of an
// assertion above the maximum level is discarded rather than instantiated.

struct not_formattable {};

void try_compile_3()
{
	aw_assert_audit(true, "{}", not_formattable{});
}
