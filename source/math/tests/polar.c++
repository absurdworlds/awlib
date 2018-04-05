#include <aw/utility/test.h>
#include <aw/math/polar.h>
#include <aw/math/vector_compare.h>

#include <algorithm>

TestFile("math::polar");

namespace aw {
namespace math {
// rotate y axis into x axis
Test(polar_y_to_x) {
	degrees<double> phi{ 90 };
	degrees<double> theta{ 90 };
	double radius = 1.0f;

	auto xyz = spherical_to_cartesian( radius, phi, theta );

	TestAssert(xyz == vector3d<double>{1.0, 0.0, 0.0});
};

} // namespace math
} // namespace aw
