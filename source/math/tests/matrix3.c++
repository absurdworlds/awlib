#include <aw/utility/test.h>
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


	auto p = radians<float>{ degrees<float>{ 45.0f } }.count();
	auto y = radians<float>{ degrees<float>{ 30.0f } }.count();
	auto r = radians<float>{ degrees<float>{ 15.0f } }.count();

	auto pyr1 = matrix_from_euler<f32>( { p,y,r } );
	auto pyr2 = roll * yaw * pitch;

	TestEqual(pyr1, pyr2);
};
} // namespace math
} // namespace aw
