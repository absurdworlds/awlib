#include <aw/utility/test.h>
#include <aw/math/vector3d.h>
#include <algorithm>

TestFile("Vector");

namespace aw {
namespace math {
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
} // namespace math
} // namespace aw

RunTests();
