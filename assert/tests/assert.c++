#include <aw/assert.h>

#include <aw/utility/test.h>

#include <iostream>

TestFile( "assert" );

#undef assert

namespace aw {

assert_action assert_fail(string_view assertion, source_location location)
{
	std::cerr << "ASSERTION FAILED:" << assertion << " in file " << location.file_name() << " on line " << location.line() << '\n';
	return assert_action::ignore;
}

Test(assert_compile_test)
{
	install_assert_handler(assert_fail);

	aw::assert([] { return false; }, "assert");

	//aw_assert(true, "message: %1", "1");
}
} // namespace aw

#include <aw/test/test_runner.h>
