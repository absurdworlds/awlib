#include <aw/test/test.h>
#include <aw/math/rect.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/vector.h>

TestFile("math::rect");

namespace aw::math {
Test(rect_construction) {
	rect<int> from_scalars{1, 2, 5, 8};
	rect<int> from_vectors{{1, 2}, {5, 8}};
	rect<int> zero;

	Checks {
		TestEqual(from_scalars.upper_left,  from_vectors.upper_left);
		TestEqual(from_scalars.lower_right, from_vectors.lower_right);

		TestEqual(zero.upper_left,  (vector2d<int>{0, 0}));
		TestEqual(zero.lower_right, (vector2d<int>{0, 0}));
	}
};

Test(rect_extents) {
	rect<int> r{1, 2, 5, 8};

	Checks {
		TestEqual(r.width(),  4);
		TestEqual(r.height(), 6);
		TestEqual(r.center(), (vector2d<int>{3, 5}));
	}
};

Test(rect_center_of_float_rect) {
	rect<double> r{0.0, 0.0, 1.0, 3.0};

	Checks {
		TestEqual(r.center(), (vector2d<double>{0.5, 1.5}));
	}
};

Test(rect_set_width_leaves_height_alone) {
	rect<int> r{1, 2, 5, 8};

	Checks {
		r.set_width(10);

		TestEqual(r.width(),  10);
		TestEqual(r.height(), 6);
		TestEqual(r.lower_right, (vector2d<int>{11, 8}));
	}
};

Test(rect_set_height_leaves_width_alone) {
	rect<int> r{1, 2, 5, 8};

	Checks {
		r.set_height(10);

		TestEqual(r.width(),  4);
		TestEqual(r.height(), 10);
		TestEqual(r.lower_right, (vector2d<int>{5, 12}));
	}
};

Test(rect_set_position) {
	rect<int> r{1, 2, 5, 8};

	Checks {
		r.set_position({10, 20});

		TestEqual(r.upper_left,  (vector2d<int>{10, 20}));
		TestEqual(r.lower_right, (vector2d<int>{14, 26}));
		TestEqual(r.width(),  4);
		TestEqual(r.height(), 6);
	}
};

Test(rect_arithmetic) {
	rect<int> r{1, 2, 5, 8};

	Checks {
		auto sum = r + rect<int>{1, 1, 1, 1};
		TestEqual(sum.upper_left,  (vector2d<int>{2, 3}));
		TestEqual(sum.lower_right, (vector2d<int>{6, 9}));

		auto diff = r - rect<int>{1, 1, 1, 1};
		TestEqual(diff.upper_left,  (vector2d<int>{0, 1}));
		TestEqual(diff.lower_right, (vector2d<int>{4, 7}));

		auto moved = r;
		moved += vector2d<int>{3, 4};
		TestEqual(moved.upper_left,  (vector2d<int>{4, 6}));
		TestEqual(moved.lower_right, (vector2d<int>{8, 12}));

		moved -= vector2d<int>{3, 4};
		TestEqual(moved.upper_left,  r.upper_left);
		TestEqual(moved.lower_right, r.lower_right);
	}
};

Test(rect_contains) {
	rect<int> r{1, 2, 5, 8};

	Checks {
		TestAssert(contains(r, vector2d<int>{3, 5}));

		// edges count as inside
		TestAssert(contains(r, r.upper_left));
		TestAssert(contains(r, r.lower_right));

		TestAssert(!contains(r, vector2d<int>{0, 5}));
		TestAssert(!contains(r, vector2d<int>{6, 5}));
		TestAssert(!contains(r, vector2d<int>{3, 1}));
		TestAssert(!contains(r, vector2d<int>{3, 9}));
	}
};
} // namespace aw::math
