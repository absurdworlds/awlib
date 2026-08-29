#include <aw/test/test.h>
#include <aw/string/to_string/math/vector.h>
#include <aw/math/vector3d.h>
#include <aw/math/vector_compare.h>
#include <aw/types/traits/basic_traits.h>
#include <algorithm>

TestFile("Vector");

namespace aw {
namespace math {
/*
 * The math types are plain aggregates of scalars, and both awlib and its
 * users rely on copying them being a memcpy: containers relocate them, and
 * they are passed in registers.
 *
 * Hand-writing a copy assignment makes the type non-trilially copyable,
 * so the simplest way is to declare none of the assignment operators,
 * except the templated ones, which are not copy-assignment operators and
 * should not affect triviality.
 */
static_assert(is_trivially_copyable<vector<float,2>>);
static_assert(is_trivially_copyable<vector<float,3>>);
static_assert(is_trivially_copyable<vector<double,4>>);
static_assert(std::is_standard_layout_v<vector<float,3>>);
// no user-provided constructors, so it can also live in uninitialised storage
static_assert(std::is_trivial_v<vector<float,3>>);
static_assert(sizeof(vector<float,3>) == 3 * sizeof(float));

Test(vec_copy_assignment) {
	vector3d<int> src {1, 2, 3};
	vector3d<int> dst {0, 0, 0};

	Checks {
		dst = src;

		TestEqual(dst, src);
		TestEqual(dst, (vector3d<int>{1, 2, 3}));
	}

	Postconditions {
		// assignment copies, it does not alias
		src = vector3d<int>{9, 9, 9};
		TestEqual(dst, (vector3d<int>{1, 2, 3}));
	}
}

Test(vec_narrow_assignment_keeps_extra_elements) {
	vector<int,4> dst {1, 2, 3, 4};
	vector<int,2> src {8, 9};

	Checks {
		dst = src;

		// Does not affect the tail
		TestEqual(dst, (vector<int,4>{8, 9, 3, 4}));
	}
}

Test(vec_addition) {
	vector3d<int> a {  };
	vector3d<int> b { 0, 0, 0 };
	vector3d<int> c { 3, 2, 1 };
	vector3d<int> d {  };
	vector3d<int> e {  };

	Preconditions {
		// TODO: variadic equal
		TestEqualV(a.x(), b.x(), 0);
		TestEqualV(a.y(), b.y(), 0);
		TestEqualV(a.z(), b.z(), 0);
	}

	Checks {
		a += c;
		b = b + c;
		d = a - c;
		e = a + -c;
	}

	Postconditions {
		TestEqualV(a.x(), b.x(), c.x());
		TestEqualV(a.y(), b.y(), c.y());
		TestEqualV(a.z(), b.z(), c.z());
		TestEqualV(d.z(), e.z(), 0);
		TestEqualV(d.z(), e.z(), 0);
		TestEqualV(d.z(), e.z(), 0);
	}
};

Test(vec_cast) {
	vector3d<int> a {1,2,3};
	vector3d<float> b {1.0,2.0,3.0};
	auto c = vector3d<float>(a);

	Checks {
		TestEqual( c[0], b[0] );
		TestEqual( c[1], b[1] );
		TestEqual( c[2], b[2] );
	};
};

Test(vec_apply) {
	vector3d<int> a{1,2,3};
	vector3d<float> b{0.5,1,1.5};

	auto func = [] (int x) {
		return float(x) / 2;
	};

	auto c = a.apply( func );
	TestEqual( c[0], b[0] );
	TestEqual( c[1], b[1] );
	TestEqual( c[2], b[2] );
};

Test(vec_cross) {
	vector3d<int> x{1,0,0};
	vector3d<int> y{0,1,0};
	vector3d<int> z{0,0,1};

	vector3d<int> o{0,0,0};

	auto x_x = cross(x,x);
	auto x_y = cross(x,y);
	auto y_x = cross(y,x);
	auto z_y = cross(z,y);

	TestEqual(x_x, o);
	TestEqual(x_y, z);
	TestEqual(x_y, -y_x);
	TestEqual(z_y, -x);
};
} // namespace math
} // namespace aw
