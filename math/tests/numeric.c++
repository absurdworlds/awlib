#include <aw/test/test.h>
#include <aw/math/numeric.h>

TestFile("math::numeric");

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

Test(is_power_of_2) {
	TestAssert( is_power_of_2(1) );
	TestAssert( is_power_of_2(2) );
	TestAssert( is_power_of_2(1024) );
	TestAssert( !is_power_of_2(0) );
	TestAssert( !is_power_of_2(3) );
	TestAssert( !is_power_of_2(1023) );
};
} // namespace aw::math
