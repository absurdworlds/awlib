#include <aw/test/test.h>
#include <aw/math/matrix3.h>
#include <aw/math/matrix_compare.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/matrix.h>
#include <aw/string/to_string/math/vector.h>

#include <algorithm>

TestFile("Matrix 3x3");

namespace aw {
namespace math {
Test(matrix3_pyr) {
	auto pitch = pitch_matrix( degrees<float>{ 45.0f } );
	auto yaw   = yaw_matrix( degrees<float>{ 30.0f } );
	auto roll  = roll_matrix( degrees<float>{ 15.0f } );


	auto p = degrees<float>{ 45.0f };
	auto y = degrees<float>{ 30.0f };
	auto r = degrees<float>{ 15.0f };

	auto pyr1 = matrix_from_euler( vector{ p,y,r } );
	auto pyr2 = roll * yaw * pitch;

	TestEqual(pyr1, pyr2);
};

Test(matrix3_scale)
{
	auto const rot = matrix_from_euler( vector3d<radians<double>>{
		radians<double>{0.4}, radians<double>{0.3}, radians<double>{0.2} } );

	vector3d<double> const scl{ 2, 3, 4 };

	auto scaled = rot;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			scaled.get(i, j) *= scl[i];

	Checks {
		TestEqual( scale_positive(scaled), scl );
		TestEqual( scale(scaled), scl );
	}

	Checks {
		// a pure rotation carries no scale
		TestEqual( scale_positive(rot), vector3d<double>{1, 1, 1} );
	}

	Checks {
		// a negative determinant is charged to the X axis
		auto mirrored = rot;
		for (size_t j = 0; j < 3; ++j)
			mirrored.get(0, j) = -mirrored.get(0, j);

		TestEqual( scale(mirrored),          vector3d<double>{-1, 1, 1} );
		TestEqual( scale_positive(mirrored), vector3d<double>{ 1, 1, 1} );
	}
}

Test(matrix3_rotation)
{
	auto rot = yaw_matrix( degrees<float>( 90.0f ) );

	TestEqual( determinant( rot ), 1.0f );

	/*
	 *    y                 y    z
	 *    |                 |   /
	 *    |                 |  /
	 *    |                 | /
	 *    |_________ z  ->  |/_________ x
	 *    /
	 *   /
	 *  /
	 * /
	 * x
	 *
	 */
	vector3d<float> vec{1,0,0};

	vector3d<float> expected{0,0,-1};

	vec = rot * vec;
	TestEqual(vec, expected);
}
} // namespace math
} // namespace aw
