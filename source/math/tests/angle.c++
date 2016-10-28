#include <aw/utility/test.h>
#include <aw/math/angle.h>

#include <algorithm>

TestFile("math::angle");

namespace aw {
namespace math {
Test(angle_conversion) {
	degrees<f32> d1{ 30 };
	radians<f32> r1{ pi/6 };

	degrees<f32> d2{ r1 };

	TestEqual(d1.count(), d2.count());
};
} // namespace math
} // namespace aw
