#include <aw/bit/count.h>
#include <aw/test/test.h>

TestFile( "bit::count" );

namespace aw::bit {
Test(count_leading_zeros)
{
	Checks {
		TestEqual(leading_zeros(u32(0b1000)), 28);
		TestEqual(leading_zeros(u32(1)), 31);
		TestEqual(leading_zeros(u32(0x80000000)), 0);
		TestEqual(leading_zeros(u32(0)), 32);
	};

	Checks {
		TestEqual(leading_zeros(u64(0b1000)), 60);
		TestEqual(leading_zeros(u64(1)), 63);
		TestEqual(leading_zeros(u64(1) << 63), 0);
		TestEqual(leading_zeros(u64(0)), 64);
	};
}

Test(count_trailing_zeros)
{
	Checks {
		TestEqual(trailing_zeros(u32(0b1000)), 3);
		TestEqual(trailing_zeros(u32(1)), 0);
		TestEqual(trailing_zeros(u32(0x80000000)), 31);
		TestEqual(trailing_zeros(u32(0)), 32);
	};

	Checks {
		TestEqual(trailing_zeros(u64(0b1000)), 3);
		TestEqual(trailing_zeros(u64(1)), 0);
		TestEqual(trailing_zeros(u64(1) << 63), 63);
		TestEqual(trailing_zeros(u64(0)), 64);
	};
}

Test(count_single_bit)
{
	// For a value with one bit set, the zeros on either side
	// add up to one less than the width of the type
	Checks {
		for (size_t i = 0; i < 32; ++i) {
			TestEqual(leading_zeros(u32(1) << i), 31 - i);
			TestEqual(trailing_zeros(u32(1) << i), i);
		}
	};

	Checks {
		for (size_t i = 0; i < 64; ++i) {
			TestEqual(leading_zeros(u64(1) << i), 63 - i);
			TestEqual(trailing_zeros(u64(1) << i), i);
		}
	};
}

Test(count_aliases)
{
	Checks {
		TestEqual(clz(u32(0b1000)), leading_zeros(u32(0b1000)));
		TestEqual(ctz(u32(0b1000)), trailing_zeros(u32(0b1000)));
	};
}
} // namespace aw::bit
