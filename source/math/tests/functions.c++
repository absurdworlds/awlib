#include <aw/math/math.h>
#include <aw/utility/test.h>

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
} // namespace math
} // namespace aw
