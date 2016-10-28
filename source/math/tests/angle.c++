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
	degrees<f32> d3{ 60 };
	degrees<f32> d4{ 30 };

	TestEqual(d1.count(), d2.count());
	TestEqual(d3.count(), (d1+r1).count());
	TestEqual(d3.count(), (2*d1).count());
	TestEqual((d1*2).count(), (2*d1).count());
	TestEqual((d4+d1).count(), (d1+d1).count());
};

} // namespace math
} // namespace aw
