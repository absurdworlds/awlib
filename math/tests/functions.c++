#include <aw/math/math.h>
#include <aw/test/test.h>

TestFile("math::functions");

namespace aw {
namespace math {
Test(div_round) {
	Preconditions {
		TestEqual( div_round(1,2), 1 ); // or should it be 0?
		TestEqual( div_round(1,3), 0 );
		TestEqual( div_round(3,2), 2 );
		TestEqual( div_round(3,2), 2 );
		TestEqual( div_round(5,2), 3 );
		TestEqual( div_round(11,3), 4 );
		TestEqual( div_round(10,3), 3 );
		TestEqual( div_round(131777, 1111), 119 );
		TestEqual( div_round(133777, 1111), 120 );
	}

	Preconditions {
		//TestGreater( div_round(131777, 1111), 131777/1111 )
		TestAssert( div_round(131777, 1111) > 131777/1111 );
		TestAssert( div_round(133777, 1111) == 133777/1111 );
	}
};

Test(div_floor) {
	TestEqual( div_floor(1,2), 0 );
	TestEqual( div_floor(100,2), 50 );
	TestEqual( div_floor(101,2), 50 );
	TestEqual( div_floor(102,2), 51 );
	TestEqual( div_floor(5,3), 1 );
	TestEqual( div_floor(-5,3), -2 );
};

Test(sign) {
	TestEqual( sign(-100), -1 );
	TestEqual( sign(0), 0 );
	TestEqual( sign(100), 1 );

	TestEqual( sign(-100.f), -1.f );
	TestEqual( sign(-0.f), -0.f );
	TestEqual( sign(0.f), 0.f );
	TestEqual( sign(100.f), 1.f );
};

Test(lerp) {
	TestEqual( lerp(1.0,2.0,0.5), 1.5 );
};
} // namespace math
} // namespace aw
