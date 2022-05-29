#include <aw/utility/test.h>
#include <aw/math/quaternion.h>
#include <aw/math/vector_compare.h>
#include <aw/utility/to_string/math/vector.h>
#include <algorithm>

TestFile("math::quaternion");

namespace aw {
namespace math {
Test(quaternion) {
	vector3d<float> rot1 { pi/2, 0, 0 };
	
	Checks {
		auto quat = quaternion<float>::from_euler( pi/2, 0, 0 );
		auto rot  = quat.to_euler();
		TestEqual( rot, rot1 );
	}

};
} // namespace math
} // namespace aw
