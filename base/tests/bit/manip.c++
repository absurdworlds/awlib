#include <aw/bit/manip.h>
#include <aw/test/test.h>

TestFile( "bit::manip" );

namespace aw::bit {
Test(manip_halves)
{
	Checks {
		TestEqual(lower_half(u32(0x4)), 0x4);
		TestEqual(lower_half(u64(0b1000)), 0b1000);
		TestEqual(lower_half(u64(0x1'00000004)), 0x4);
		TestEqual(upper_half(u64(0x1'00000004)), 0x1);
		TestEqual(upper_half(u32(0xabcd1234)), 0xabcd);
		TestEqual(lower_to_upper(u32(0x1234)), 0x12340000);
	};
}

Test(manip_single_bits)
{
	Checks {
		TestEqual(get_bit(0b100000, 5), 1);
		TestEqual(get_bit(0b100000, 4), 0);
		TestEqual(top_bit(u8(0x80)), 1);
		TestEqual(top_bit(u8(0x7f)), 0);
		TestEqual(set_bit(0b100000, 4, 1), 0b110000);
		TestEqual(set_bit(0b110000, 4, 0), 0b100000);
		TestEqual(swap_bits(0b01000, 3, 4), 0b10000);
	};
}

Test(manip_set_bit_wide)
{
	Checks {
		// Bits above the width of int can be set
		TestEqual(set_bit(u64(0), 31, 1), u64(1) << 31);
		TestEqual(set_bit(u64(0), 63, 1), u64(1) << 63);
	};
}

Test(manip_rotate)
{
	Checks {
		TestEqual(rotl(u32(0x80000001), 1), u32(0x00000003));
		TestEqual(rotr(u32(0x00000003), 1), u32(0x80000001));
		TestEqual(rotl(u8(0b1000'0001), 1), u8(0b0000'0011));
		TestEqual(rotr(u8(0b1000'0001), 1), u8(0b1100'0000));
		TestEqual(rotr(u64(1), 1), u64(1) << 63);
		TestEqual(rotl(u64(0x80000000'00000001), 1), u64(0x00000000'00000003));
		TestEqual(rotr(u64(0x80000000'00000001), 1), u64(0xc0000000'00000000));

		// Rotating by zero leaves the value alone
		TestEqual(rotl(u32(0x12345678), 0), u32(0x12345678));
		TestEqual(rotr(u32(0x12345678), 0), u32(0x12345678));
	};
}


/*!
 * Rotating left by r and right by the bits that remain
 * describe the same rotation
 */
Test(manip_rotate_round_trip)
{
	Checks {
		for (size_t r = 1; r < 32; ++r)
			TestEqual(rotl(u32(0xdeadbeef), r), rotr(u32(0xdeadbeef), 32 - r));
	};
}
} // namespace aw::bit
