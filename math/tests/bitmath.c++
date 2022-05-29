#include <aw/test/test.h>
#include <aw/math/bitmath.h>

TestFile("math::bitmath");

namespace aw {
namespace math {
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
} // namespace math
} // namespace aw
