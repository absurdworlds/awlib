#include <aw/assert.h>

#include <aw/test/test.h>

#include <iostream>

TestFile( "assert" );

namespace aw {

const string_view expected_assertions[] ={
    "assert",
    "false",
    "1 == 2",
    "false_with_message",
    "false_with_formatted_message"
};

const string_view* current_assertion = &expected_assertions[0];

assert_action test_assert_handler(string_view assertion, source_location location)
{
	if (current_assertion > std::end(expected_assertions))
	{
		TestFail("Too many assertions!");
	}
	else
	{
		// Check that we got the correct assertion
		TestEqual(*current_assertion++, assertion);

		// Check that it doesn't use the location of the assert header
		TestEqual(location.file_name(), string_view(__FILE__));
	}
	return assert_action::ignore;
}

Test(assert_basic_test)
{
	const auto old_handler = install_assert_handler(test_assert_handler);

	aw::assert([] { return false; }, "assert");
	aw::assert([] { return true; }, "no assert");

	aw_assert(true, "assert: {}", "1");
	aw_assert(false);
	aw_assert(1 == 2);
	aw_assert(2 * 2 == 4);
	aw_assert(false, "false_with_message");
	aw_assert(false, "false_with_{}_message", "formatted");

	install_assert_handler(old_handler);
}
} // namespace aw

#include <aw/test/test_runner.h>
