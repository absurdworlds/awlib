#include <aw/utility/string/conv/integer.h>
#include <aw/test/test.h>

TestFile("string_conv_integer");

namespace aw {
Test(int_converter_radix_36)
{
	Checks {
		// Test that radix 36 compiles and works
		int_converter<36, 10> conv;
		conv.sign = false;
		conv.top_digit = 0;
		conv.digits[0] = 0;

		// Manually set digits to represent "Z" (35 in base 36)
		conv.digits[0] = 35;
		conv.top_digit = 0;
		TestEqual(conv.to_string(), std::string("Z"));

		// Represent "10" in base 36 (which is 36 in decimal)
		conv.digits[0] = 0;
		conv.digits[1] = 1;
		conv.top_digit = 1;
		TestEqual(conv.to_string(), std::string("10"));

		// Represent "A" (10 in base 36)
		conv.digits[0] = 10;
		conv.top_digit = 0;
		TestEqual(conv.to_string(), std::string("A"));

		// Represent "ZY" (35*36 + 34 = 1294 in decimal)
		conv.digits[0] = 34;
		conv.digits[1] = 35;
		conv.top_digit = 1;
		TestEqual(conv.to_string(), std::string("ZY"));

		// Test with sign
		conv.sign = true;
		conv.digits[0] = 10;
		conv.top_digit = 0;
		TestEqual(conv.to_string(), std::string("-A"));
	};
}

Test(int_converter_radix_2)
{
	Checks {
		int_converter<2, 10> conv;
		conv.sign = false;
		conv.top_digit = 0;
		conv.digits[0] = 1;
		TestEqual(conv.to_string(), std::string("1"));

		conv.digits[0] = 0;
		conv.digits[1] = 1;
		conv.top_digit = 1;
		TestEqual(conv.to_string(), std::string("10"));
	};
}

Test(int_converter_radix_16)
{
	Checks {
		int_converter<16, 10> conv;
		conv.sign = false;
		conv.top_digit = 0;
		conv.digits[0] = 15;
		TestEqual(conv.to_string(), std::string("F"));

		conv.digits[0] = 10;
		TestEqual(conv.to_string(), std::string("A"));

		conv.digits[0] = 0;
		conv.digits[1] = 1;
		conv.top_digit = 1;
		TestEqual(conv.to_string(), std::string("10"));
	};
}

Test(int_converter_radix_35)
{
	Checks {
		// Test that radix 35 also works (edge case below 36)
		// In radix 35, valid digits are 0-9 and A-Y (35 chars), so 34 maps to Y
		int_converter<35, 10> conv;
		conv.sign = false;
		conv.top_digit = 0;
		conv.digits[0] = 34;
		TestEqual(conv.to_string(), std::string("Y"));
	};
}
} // namespace aw
