#include <aw/test/test.h>
#include <aw/math/plane.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/vector.h>

#include <aw/types/traits/basic_traits.h>

TestFile("math::plane");

namespace aw::math {
// Kept trivially copyable; see the note in vector.c++
static_assert(is_trivially_copyable<plane<float>>);
static_assert(is_trivially_copyable<plane<double>>);
static_assert(std::is_standard_layout_v<plane<float>>);

Test(plane_copy_assignment) {
	using vec3 = vector3d<double>;

	plane<double> src{vec3{0, 2, 0}, vec3{0, 1, 0}};
	plane<double> dst{vec3{5, 5, 5}, vec3{1, 0, 0}};

	Checks {
		dst = src;

		TestEqual(dst.normal(), src.normal());
		TestEqual(dst.distance_to_point(vec3{0, 5, 0}),
		          src.distance_to_point(vec3{0, 5, 0}));
	}

	Postconditions {
		// assignment copies, it does not alias
		src = plane<double>{vec3{0, 0, 0}, vec3{1, 0, 0}};

		TestEqual(dst.normal(), (vec3{0, 1, 0}));
		TestEqual(dst.distance_to_point(vec3{0, 5, 0}), 3.0);
	}
};
} // namespace aw::math
