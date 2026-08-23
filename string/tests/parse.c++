#include <aw/string/parse.h>
#include <aw/test/test.h>

#include <aw/string/to_string/optional.h>

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

		// only the one sign belongs to the number
		TestEqual(string::parse<int>("+-123"), std::nullopt);
		TestEqual(string::parse<int>("-+123"), std::nullopt);
		TestEqual(string::parse<int>("--1"),   std::nullopt);
		TestEqual(string::parse<int>("++1"),   std::nullopt);
		TestEqual(string::parse<double>("+-1.5"), std::nullopt);
		TestEqual(string::parse<double>("-+1.5"), std::nullopt);
		TestEqual(string::parse<double>("--1.5"), std::nullopt);
		TestEqual(string::parse<double>("++1.5"), std::nullopt);

		// also the same with prefixes
		TestEqual(string::parse<int>("+-0x10"), std::nullopt);
		TestEqual(string::parse<int>("-+0x10"), std::nullopt);
		TestEqual(string::parse<int>("--0x10"), std::nullopt);
		TestEqual(string::parse<int>("++0x10"), std::nullopt);

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
		TestEqual(string::parse<int>("0z10"),  std::nullopt);
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

/*!
 * A base prefix picks how the digits are read; without one they are decimal.
 */
Test(parse_base_prefix) {
	Checks {
		TestEqual(string::parse<int>("0x10"),   16);
		TestEqual(string::parse<int>("0X1f"),   31);
		TestEqual(string::parse<int>("0b1010"), 10);
		TestEqual(string::parse<int>("0o17"),   15);
		TestEqual(string::parse<int>("0d17"),   17);

		// a leading zero on its own is not octal
		TestEqual(string::parse<int>("010"), 10);
		TestEqual(string::parse<int>("0"),    0);

		// the sign comes before the prefix
		TestEqual(string::parse<int>("-0x10"), -16);
		TestEqual(string::parse<int>("+0b11"),   3);
		TestEqual(string::parse<unsigned>("-0x10"), std::nullopt);

		// the whole string still has to be a number
		TestEqual(string::parse<int>("0x"),    std::nullopt);
		TestEqual(string::parse<int>("0b12"),  std::nullopt);
		TestEqual(string::parse<int>("0x10z"), std::nullopt);
	}
}

/*!
 * Floating point numbers are decimal, or hexadecimal with `0x`.
 */
Test(parse_hex_float) {
	Checks {
		TestEqual(string::parse<double>("0x1.8p3"),  12.0);
		TestEqual(string::parse<double>("-0x1.8p3"), -12.0);
		TestEqual(string::parse<double>("0x1.8"),    1.5);

		TestEqual(string::parse<double>("0b101"), std::nullopt);
		TestEqual(string::parse<double>("0o17"),  std::nullopt);
		TestEqual(string::parse<double>("0d17"),  std::nullopt);
	}
}

/*!
 * A prefixed number is has the same limits as a plain one.
 */
Test(parse_prefix_limits) {
	Checks {
		TestEqual(string::parse<int>("-0x80000000"), std::numeric_limits<int>::min());
		TestEqual(string::parse<int>("0x80000000"),  std::nullopt);
		TestEqual(string::parse<int>("-0x80000001"), std::nullopt);

		TestEqual(string::parse<unsigned>("0xffffffff"),  4294967295u);
		TestEqual(string::parse<unsigned>("0x100000000"), std::nullopt);
	}
}
} // namespace aw
