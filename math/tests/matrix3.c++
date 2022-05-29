#include <aw/test/test.h>
#include <aw/math/matrix3.h>
#include <aw/math/matrix_compare.h>
#include <aw/utility/to_string/math/matrix.h>

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
