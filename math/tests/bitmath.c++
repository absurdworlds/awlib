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
} // namespace aw::math
