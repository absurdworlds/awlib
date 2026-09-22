#include <aw/math/math.h>
#include <aw/math/vector3d.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/vector.h>
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

Test(div_ceil) {
	TestEqual( div_ceil(1,2), 1 );
	TestEqual( div_ceil(100,2), 50 );
	TestEqual( div_ceil(101,2), 51 );
	TestEqual( div_ceil(102,2), 51 );
	TestEqual( div_ceil(5,3), 2 );
	TestEqual( div_ceil(-5,3), -1 );

	TestEqual( div_ceil(5u,3u), 2u );
	TestEqual( div_ceil(6u,3u), 2u );
}

Test(round_down) {
	TestEqual( round_down(7, 3), 6 );
	TestEqual( round_down(6, 3), 6 );
	TestEqual( round_down(-7, 3), -9 );
	TestEqual( round_down(-6, 3), -6 );

	TestEqual( round_down(7.5, 3.0), 6.0 );
	TestEqual( round_down(-7.5, 3.0), -9.0 );

	// a step of a different type widens the result
	TestEqual( round_down(7, 2.5), 5.0 );

	static_assert( round_down(7, 3) == 6 );
	static_assert( round_down(7.5, 3.0) == 6.0 );
}

Test(round_up) {
	TestEqual( round_up(7, 3), 9 );
	TestEqual( round_up(6, 3), 6 );
	TestEqual( round_up(-7, 3), -6 );
	TestEqual( round_up(-6, 3), -6 );

	TestEqual( round_up(7.5, 3.0), 9.0 );
	TestEqual( round_up(-7.5, 3.0), -6.0 );

	TestEqual( round_up(7, 2.5), 7.5 );

	static_assert( round_up(7, 3) == 9 );
	static_assert( round_up(7.5, 3.0) == 9.0 );
}

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

Test(lerp_vector) {
	using vec3 = vector3d<float>;

	vec3 a {0, 0, 0};
	vec3 b {2, 4, 6};

	Checks {
		TestEqual( lerp(a, b, 0.0), a );
		TestEqual( lerp(a, b, 1.0), b );
		TestEqual( lerp(a, b, 0.5), (vec3{1, 2, 3}) );
	}
}

Test(lerp_vector_of_double) {
	using vec3 = vector3d<double>;

	vec3 a {1, 1, 1};
	vec3 b {3, 5, 9};

	Checks {
		TestEqual( lerp(a, b, 0.5), (vec3{2, 3, 5}) );
	}
}
} // namespace math
} // namespace aw
