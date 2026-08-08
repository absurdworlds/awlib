#include <aw/bit/mask.h>
#include <aw/test/test.h>

TestFile( "bit::mask" );

namespace aw::bit {
Test(mask_single_bit)
{
	Checks {
		TestEqual(bit(0), uintmax_t(1));
		TestEqual(bit(1), uintmax_t(2));
		TestEqual(bit(4), uintmax_t(0b10000));
		TestEqual(bit(30), uintmax_t(1) << 30);
		// Bits above the width of int are reachable
		TestEqual(bit(31), uintmax_t(1) << 31);
		TestEqual(bit(32), uintmax_t(1) << 32);
		TestEqual(bit(63), uintmax_t(1) << 63);
	};
}

Test(mask_lower)
{
	Checks {
		TestEqual(lower_mask<u64>(2), 0b11);
		TestEqual(lower_mask<u64>(4), 0b1111);
		TestEqual(lower_mask<u32>(8), 0xff);
	};
}

Test(mask_upper)
{
	Checks {
		TestEqual(upper_mask<u16>(8), 0xff00);
		TestEqual(upper_mask<u64>(4), 0xf0);
	};
}

Test(mask_halves)
{
	Checks {
		TestEqual(lower_bits<u32>, 0x0000ffff);
		TestEqual(upper_bits<u32>, 0xffff0000);
		TestEqual(lower_bits<u64>, 0x00000000'ffffffff);
		TestEqual(upper_bits<u64>, 0xffffffff'00000000);
	};
}
} // namespace aw::bit
