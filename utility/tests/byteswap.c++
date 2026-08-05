#include <aw/utility/byteswap.h>
#include <aw/test/test.h>

TestFile( "byteswap" );

namespace aw {
Test(byteswap_u16)
{
	Checks {
		TestEqual(byteswap(u16(0x0000)), u16(0x0000));
		TestEqual(byteswap(u16(0xFFFF)), u16(0xFFFF));
		TestEqual(byteswap(u16(0x1234)), u16(0x3412));
		TestEqual(byteswap(u16(0x00FF)), u16(0xFF00));
		TestEqual(byteswap(u16(0xFF00)), u16(0x00FF));
	};
}

Test(byteswap_u32)
{
	Checks {
		TestEqual(byteswap(u32(0x00000000)), u32(0x00000000));
		TestEqual(byteswap(u32(0xFFFFFFFF)), u32(0xFFFFFFFF));
		TestEqual(byteswap(u32(0x12345678)), u32(0x78563412));
		TestEqual(byteswap(u32(0x000000FF)), u32(0xFF000000));
		TestEqual(byteswap(u32(0xFF000000)), u32(0x000000FF));
		TestEqual(byteswap(u32(0x0000FF00)), u32(0x00FF0000));
	};
}

Test(byteswap_u64)
{
	Checks {
		TestEqual(byteswap(u64(0x0000000000000000)), u64(0x0000000000000000));
		TestEqual(byteswap(u64(0xFFFFFFFFFFFFFFFF)), u64(0xFFFFFFFFFFFFFFFF));
		TestEqual(byteswap(u64(0x0123456789ABCDEF)), u64(0xEFCDAB8967452301));
		TestEqual(byteswap(u64(0x00000000000000FF)), u64(0xFF00000000000000));
		TestEqual(byteswap(u64(0xFF00000000000000)), u64(0x00000000000000FF));
		TestEqual(byteswap(u64(0x0000000100000000)), u64(0x0000000001000000));
	};
}

Test(byteswap_signed)
{
	Checks {
		TestEqual(byteswap(i16(0x1234)), i16(0x3412));
		TestEqual(byteswap(i32(0x12345678)), i32(0x78563412));
		TestEqual(byteswap(i64(0x0123456789ABCDEF)), i64(0xEFCDAB8967452301));

		// the sign bit always moves into another byte, so -1 is the only
		// negative value which stays negative
		TestEqual(byteswap(i16(-1)), i16(-1));
		TestEqual(byteswap(i32(-1)), i32(-1));
		TestEqual(byteswap(i64(-1)), i64(-1));

		TestEqual(byteswap(i16(-2)), i16(0xFEFF));
		TestEqual(byteswap(i32(-2)), i32(0xFEFFFFFF));
		TestEqual(byteswap(i64(-2)), i64(0xFEFFFFFFFFFFFFFF));
	};
}

namespace {
constexpr u64 samples[] = {
	0x0000000000000000, 0x0000000000000001, 0x00000000000000FF,
	0x0123456789ABCDEF, 0xDEADBEEFCAFEBABE, 0x8000000000000001,
	0x00FF00FF00FF00FF, 0xFFFFFFFFFFFFFFFF,
};
} // namespace

// swapping twice must return the original value
Test(byteswap_involution)
{
	Checks {
		for (auto val : samples) {
			TestEqual(byteswap(byteswap(u64(val))), u64(val));
			TestEqual(byteswap(byteswap(u32(val))), u32(val));
			TestEqual(byteswap(byteswap(u16(val))), u16(val));
			TestEqual(byteswap(byteswap(i64(val))), i64(val));
			TestEqual(byteswap(byteswap(i32(val))), i32(val));
			TestEqual(byteswap(byteswap(i16(val))), i16(val));
		}
	};
}

// each byte must land in the mirrored position
Test(byteswap_byte_positions)
{
	Checks {
		for (int i = 0; i < 2; ++i)
			TestEqual(byteswap(u16(u16(0xA5) << (8*i))), u16(u16(0xA5) << (8*(1-i))));

		for (int i = 0; i < 4; ++i)
			TestEqual(byteswap(u32(u32(0xA5) << (8*i))), u32(u32(0xA5) << (8*(3-i))));

		for (int i = 0; i < 8; ++i)
			TestEqual(byteswap(u64(u64(0xA5) << (8*i))), u64(u64(0xA5) << (8*(7-i))));
	};
}
} // namespace aw
