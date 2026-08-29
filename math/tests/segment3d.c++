#include <aw/test/test.h>
#include <aw/math/segment3d.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/vector.h>

TestFile("math::segment3d");

namespace aw::math {
using vec3 = vector3d<double>;

Test(segment3d_construction) {
	segment3d<double> from_scalars{1, 2, 3, 4, 5, 6};
	segment3d<double> from_vectors{{1, 2, 3}, {4, 5, 6}};
	segment3d<double> zero;

	Checks {
		TestEqual(from_scalars.start, from_vectors.start);
		TestEqual(from_scalars.end,   from_vectors.end);

		TestEqual(zero.start, (vec3{0, 0, 0}));
		TestEqual(zero.end,   (vec3{0, 0, 0}));
	}
};

Test(segment3d_vector_and_length) {
	segment3d<double> seg{{1, 0, 0}, {4, 4, 0}};

	Checks {
		TestEqual(seg.to_vector(), (vec3{3, 4, 0}));
		TestEqual(seg.length(),    5.0);
		TestEqual(seg.length_sq(), 25.0);
		TestEqual(seg.direction(), (vec3{0.6, 0.8, 0.0}));
	}
};

Test(segment3d_normal_point) {
	segment3d<double> seg{{0, 0, 0}, {10, 0, 0}};

	Checks {
		TestEqual(seg.normal_point({3, 5, 0}), (vec3{3, 0, 0}));

		// projections outside the segment are not clamped
		TestEqual(seg.normal_point({-5, 2, 0}), (vec3{-5, 0, 0}));
		TestEqual(seg.normal_point({15, 2, 0}), (vec3{15, 0, 0}));
	}
};

Test(segment3d_closest_point_projects_onto_segment) {
	segment3d<double> seg{{0, 0, 0}, {10, 0, 0}};

	Checks {
		TestEqual(seg.closest_point({3, 5, 0}), (vec3{3, 0, 0}));
		TestEqual(seg.closest_point({7, -2, 0}), (vec3{7, 0, 0}));
	}
};

Test(segment3d_closest_point_clamps_to_ends) {
	segment3d<double> seg{{0, 0, 0}, {10, 0, 0}};

	Checks {
		TestEqual(seg.closest_point({-5, 2, 0}), seg.start);
		TestEqual(seg.closest_point({15, 2, 0}), seg.end);
	}
};

Test(segment3d_closest_point_of_degenerate_segment) {
	segment3d<double> seg{{2, 3, 4}, {2, 3, 4}};

	Checks {
		TestEqual(seg.closest_point({9, 9, 9}), seg.start);
	}
};
} // namespace aw::math
