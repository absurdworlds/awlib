#include <aw/test/test.h>
#include <aw/math/bitmath.h>

TestFile("math::bitmath");

namespace aw::math {
Test(log2) {
	TestEqual( log2(2), 1 );
	TestEqual( log2(3), 1 );
	TestEqual( log2(4), 2 );
	TestEqual( log2(127), 6 );
	TestEqual( log2(128), 7 );
	TestEqual( log2(1023), 9 );
	TestEqual( log2(1024), 10 );
	TestEqual( log2(1025), 10 );
};

Test(bits) {
	TestEqual( swap_bits(0b01000,3,4), 0b10000 );
	TestEqual( get_bit(0b100000,5), 1 );
	TestEqual( get_bit(0b100000,4), 0 );
	TestEqual( set_bit(0b100000,4,1), 0b110000);
};

Test(bit) {
	TestEqual( bit(0), uintmax_t(1) );
	TestEqual( bit(1), uintmax_t(2) );
	TestEqual( bit(30), uintmax_t(1) << 30 );
	TestEqual( bit(31), uintmax_t(1) << 31 );
	TestEqual( bit(32), uintmax_t(1) << 32 );
	TestEqual( bit(63), uintmax_t(1) << 63 );
}


Test(mask) {
	TestEqual( lower_mask<u64>(2), 0b11 );
	TestEqual( lower_mask<u64>(4), 0b1111 );
	TestEqual( lower_half(u32(0x4)), 0x4 );
	TestEqual( lower_half(u64(0b1000)), 0b1000 );
	TestEqual( lower_half(u64(0x1'00000004)), 0x4 );
}


Test(ctz) {
	TestEqual( trailing_zeros(u32(0b1000)), 3 );
	TestEqual( trailing_zeros(u64(0b1000)), 3 );
}

Test(clz) {
	TestEqual( leading_zeros(u32(0b1000)), 28 );
	TestEqual( leading_zeros(u64(0b1000)), 60 );
}

Test(clz_ctz_zero) {
	TestEqual( leading_zeros(u32(0)),  32 );
	TestEqual( trailing_zeros(u32(0)), 32 );
	TestEqual( leading_zeros(u64(0)),  64 );
	TestEqual( trailing_zeros(u64(0)), 64 );
}

Test(clz_ctz_edges) {
	TestEqual( leading_zeros(u32(0xffffffff)),  0 );
	TestEqual( trailing_zeros(u32(0xffffffff)), 0 );
	TestEqual( leading_zeros(u64(0xffffffff'ffffffff)),  0 );
	TestEqual( trailing_zeros(u64(0xffffffff'ffffffff)), 0 );

	TestEqual( leading_zeros(u32(1)),           31 );
	TestEqual( trailing_zeros(u32(0x80000000)), 31 );
	TestEqual( leading_zeros(u64(1)),                    63 );
	TestEqual( trailing_zeros(u64(0x80000000'00000000)), 63 );
}

Test(clz_ctz_sweep) {
	for (size_t i = 0; i < 32; ++i) {
		TestEqual( leading_zeros(u32(u32(1) << i)),  31 - i );
		TestEqual( trailing_zeros(u32(u32(1) << i)), i );
	}

	for (size_t i = 0; i < 64; ++i) {
		TestEqual( leading_zeros(u64(u64(1) << i)),  63 - i );
		TestEqual( trailing_zeros(u64(u64(1) << i)), i );
	}
}

Test(rot) {
	TestEqual( rotl(u8(0x81), 1), u8(0x03) );
	TestEqual( rotr(u8(0x81), 1), u8(0xc0) );
	TestEqual( rotl(u32(0x80000001), 1), u32(0x00000003) );
	TestEqual( rotr(u32(0x80000001), 1), u32(0xc0000000) );
	TestEqual( rotl(u64(0x80000000'00000001), 1), u64(0x00000000'00000003) );
	TestEqual( rotr(u64(0x80000000'00000001), 1), u64(0xc0000000'00000000) );

	// rotating by zero is the identity, and must not shift by the full width
	TestEqual( rotl(u32(0x12345678), 0), u32(0x12345678) );
	TestEqual( rotr(u32(0x12345678), 0), u32(0x12345678) );

	// rotl(x, r) and rotr(x, digits - r) describe the same rotation
	for (size_t r = 1; r < 32; ++r)
		TestEqual( rotl(u32(0xdeadbeef), r), rotr(u32(0xdeadbeef), 32 - r) );
}
} // namespace aw::math
