#include <aw/assert.h>

#include <aw/utility/test.h>


TestFile( "assert" );

#undef assert

namespace aw {

assert_action assert_fail(string_view assertion, source_location location)
	{
return assert_action::abort;
	}

Test(assert_compile_test)
{
	aw::assert([] { return true; }, "assert");

aw_assert(true, default, "message: %1", "1");


}
} // namespace aw

#include <aw/test/test_runner.h>
