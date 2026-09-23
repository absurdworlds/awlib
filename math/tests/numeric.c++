#include <aw/test/test.h>
#include <aw/math/numeric.h>
#include <aw/math/ratio.h>

#include <type_traits>

TestFile("math::numeric");

namespace aw::math {
static_assert(std::is_same_v<ratio_gcd<ratio<360>, ratio<360>>, ratio<360>>);
static_assert(std::is_same_v<ratio_gcd<ratio<360>, ratio<1>>,   ratio<1>>);
static_assert(std::is_same_v<ratio_gcd<ratio<1>,   ratio<360>>, ratio<1>>);
static_assert(std::is_same_v<ratio_gcd<ratio<1,2>, ratio<1,3>>, ratio<1,6>>);
static_assert(std::is_same_v<ratio_gcd<ratio<2,3>, ratio<4,9>>, ratio<2,9>>);
static_assert(std::is_same_v<ratio_gcd<ratio<-2>,  ratio<4>>,   ratio<2>>);

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
