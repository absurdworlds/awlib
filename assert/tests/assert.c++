#include <aw/assert.h>

#include <aw/test/test.h>

#include <iostream>
#include <string>

TestFile( "assert" );

namespace aw {

const string_view expected_assertions[] ={
    "assert",
    "false",
    "1 == 2",
    "false_with_message",
#if AW_FORMAT != AW_NO_FORMAT
    "false_with_formatted_message"
#else
    // with no provider behind aw::format the message is passed through as-is
    "false_with_{}_message"
#endif
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

namespace {
std::string recorded_message;
int         recorded_calls = 0;

assert_action recording_handler(string_view assertion, source_location)
{
	recorded_message.assign(assertion.begin(), assertion.end());
	++recorded_calls;
	return assert_action::ignore;
}
} // namespace

#if AW_FORMAT != AW_NO_FORMAT
Test(assert_formats_temporaries)
{
	const auto old_handler = install_assert_handler(recording_handler);

	int value = 7;
	aw_assert(false, "lvalue {}", value);
	TestEqual(string_view(recorded_message), string_view("lvalue 7"));

	aw_assert(false, "literal {}", 42);
	TestEqual(string_view(recorded_message), string_view("literal 42"));

	aw_assert(false, "temporary {}", std::string("s"));
	TestEqual(string_view(recorded_message), string_view("temporary s"));

	install_assert_handler(old_handler);
}
#endif

// an assertion as an unbraced branch must not swallow the else
Test(assert_is_one_statement)
{
	const auto old_handler = install_assert_handler(recording_handler);

	bool else_taken = false;
	if (false)
		aw_assert(true);
	else
		else_taken = true;
	TestAssert(else_taken);

	install_assert_handler(old_handler);
}

} // namespace aw

