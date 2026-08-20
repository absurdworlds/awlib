#include <aw/string/parse.h>
#include <aw/test/test.h>

#include <aw/utility/to_string/optional.h>

TestFile( "string::parse" );

namespace aw {
Test(parse_int) {
	Checks {
		TestEqual(string::parse<int>("123"), 123);
		TestEqual(string::parse<int>("x123"), std::nullopt);
		TestEqual(string::parse<int>("x123", 100), 100);
	}
	{
		int value = 111;
		TestAssert(!string::try_parse<int>("xxx", value));
		TestEqual(value, 111);
		TestAssert(string::try_parse<int>("123", value));
		TestEqual(value, 123);
	}
}

Test(parse_signs) {
	Checks {
		TestEqual(string::parse<int>("+123"), 123);
		TestEqual(string::parse<int>("-123"), -123);
		TestEqual(string::parse<double>("+1.5"), 1.5);
		TestEqual(string::parse<double>("-1.5"), -1.5);

		// a sign on its own is still not a number
		TestEqual(string::parse<int>("+"), std::nullopt);
		TestEqual(string::parse<int>("-"), std::nullopt);
		TestEqual(string::parse<int>("++1"), std::nullopt);

		// unsigned takes '+' but not '-'
		TestEqual(string::parse<unsigned>("+123"), 123u);
		TestEqual(string::parse<unsigned>("-123"), std::nullopt);
	}
}

Test(parse_out_of_range) {
	Checks {
		TestEqual(string::parse<int>("999999999999999999999999"), std::nullopt);
		TestEqual(string::parse<intmax_t>("999999999999999999999999"), std::nullopt);
		TestEqual(string::parse<double>("1e999999"), std::nullopt);
	}
}

/*!
 * Do not accept a string with trailing characters that don't belong
 * to the number
 */
Test(parse_trailing_characters) {
	Checks {
		TestEqual(string::parse<int>("12abc"), std::nullopt);
		TestEqual(string::parse<int>("12.9"),  std::nullopt);
		TestEqual(string::parse<int>("1 2"),   std::nullopt);
		TestEqual(string::parse<int>("0x10"),  std::nullopt);
		TestEqual(string::parse<double>("1.5xyz"), std::nullopt);
		TestEqual(string::parse<double>("1e5"), 1e5);
	}
	{
		// a rejected string leaves the output alone
		int value = 111;
		TestAssert(!string::try_parse<int>("12abc", value));
		TestEqual(value, 111);
	}
}
} // namespace aw
