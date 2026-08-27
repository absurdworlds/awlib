#include <aw/string/conv/integer.h>
#include <aw/test/test.h>

TestFile("string_conv_integer");

namespace aw {
Test(radix_accumulator_radix_36)
{
	Checks {
		// Test that radix 36 compiles and works
		radix_accumulator<36, 16> conv;
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
	}
}

Test(radix_accumulator_radix_2)
{
	Checks {
		radix_accumulator<2, 8> conv;
		conv.sign = false;
		conv.top_digit = 0;
		conv.digits[0] = 1;
		TestEqual(conv.to_string(), std::string("1"));

		conv.digits[0] = 0;
		conv.digits[1] = 1;
		conv.top_digit = 1;
		TestEqual(conv.to_string(), std::string("10"));
	}
}

Test(radix_accumulator_radix_16)
{
	Checks {
		radix_accumulator<16, 8> conv;
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
	}
}

Test(radix_accumulator_radix_35)
{
	Checks {
		// Test that radix 35 also works (edge case below 36)
		// In radix 35, valid digits are 0-9 and A-Y (35 chars), so 34 maps to Y
		radix_accumulator<35, 8> conv;
		conv.sign = false;
		conv.top_digit = 0;
		conv.digits[0] = 34;
		TestEqual(conv.to_string(), std::string("Y"));
	}
}

namespace {
//! Feed value's bits into conv MSB-first, the same way composite_int::to_string does
template<size_t R, size_t bits>
void add_bits(radix_accumulator<R, bits>& conv, unsigned long long value)
{
	for (size_t i = bits; i-- > 0; )
		conv.add_bit((value >> i) & 1u);
}
} // namespace

Test(radix_accumulator_add_bit_radix_36)
{
	Checks {
		// 35 stays a single digit: "Z"
		radix_accumulator<36, 8> conv;
		add_bits(conv, 35);
		TestEqual(conv.to_string(), std::string("Z"));
	}

	Checks {
		// 36 carries into a new digit: "10"
		radix_accumulator<36, 8> conv;
		add_bits(conv, 36);
		TestEqual(conv.to_string(), std::string("10"));
	}

	Checks {
		// 1294 = 35*36 + 34: "ZY"
		radix_accumulator<36, 16> conv;
		add_bits(conv, 1294);
		TestEqual(conv.to_string(), std::string("ZY"));
	}
}

// An accumulator can hold the largest value of the width it is declared with
Test(radix_accumulator_full_width)
{
	Checks {
		radix_accumulator<10, 32> conv;
		add_bits(conv, 0xffffffff);
		TestEqual(conv.to_string(), std::string("4294967295"));
	}

	Checks {
		radix_accumulator<36, 32> conv;
		add_bits(conv, 0xffffffff);
		TestEqual(conv.to_string(), std::string("1Z141Z3"));
	}

	Checks {
		radix_accumulator<2, 8> conv;
		add_bits(conv, 0xff);
		TestEqual(conv.to_string(), std::string("11111111"));
	}
}
} // namespace aw
