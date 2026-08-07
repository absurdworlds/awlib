#include <aw/test/test.h>
#include <aw/math/matrix4.h>
#include <aw/math/matrix3.h>
#include <aw/math/transform.h>
#include <aw/math/matrix_compare.h>
#include <aw/math/vector_compare.h>
#include <aw/utility/to_string/math/matrix.h>
#include <aw/utility/to_string/math/vector.h>

#include <algorithm>

TestFile("Matrix");

namespace aw {
namespace math {
Test(matrix4_identity) {
	matrix<int, 4,4> I {{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	}};

	TestEqual(I, identity_matrix<int,4>);
}

//! translation() must read back what translation_matrix() wrote
Test(matrix4_translation) {
	vector3d<double> const pos{ 1, 2, 3 };

	Checks {
		TestEqual( translation( translation_matrix(pos) ), pos );
	}

	Checks {
		auto const rot = yaw_matrix( degrees<double>{30} );
		TestEqual( translation( make_transform(pos, rot) ), pos );
	}
}
} // namespace math
} // namespace aw
