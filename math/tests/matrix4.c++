#include <aw/test/test.h>
#include <aw/math/matrix4.h>
#include <aw/math/matrix3.h>
#include <aw/math/transform.h>
#include <aw/math/matrix_compare.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/matrix.h>
#include <aw/string/to_string/math/vector.h>

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

namespace {
using vec3 = vector3d<double>;

constexpr double deg = pi / 180.0;

//! 4×4 transform holding just the rotation described by \a euler
matrix4<double> rotation_transform(vec3 const& euler)
{
	vector3d<radians<double>> const angles{
		radians<double>{euler[0]},
		radians<double>{euler[1]},
		radians<double>{euler[2]}
	};
	return make_transform( vec3{}, matrix_from_euler(angles) );
}
} // namespace

//! rotation() must invert matrix_from_euler, pitch included
Test(matrix4_rotation) {
	Checks {
		vec3 const euler{ 45*deg, 30*deg, 15*deg };
		TestEqual( rotation_unscaled( rotation_transform(euler) ), euler );
	}

	// each axis on its own -- the old code always decoded pitch as 0
	Checks {
		vec3 const pitch{ 40*deg, 0, 0 };
		TestEqual( rotation_unscaled( rotation_transform(pitch) ), pitch );
	}

	Checks {
		vec3 const yaw{ 0, 40*deg, 0 };
		TestEqual( rotation_unscaled( rotation_transform(yaw) ), yaw );
	}

	Checks {
		vec3 const roll{ 0, 0, 40*deg };
		TestEqual( rotation_unscaled( rotation_transform(roll) ), roll );
	}
}

//! the same, in f32 -- the gimbal cutoff is per-type, so exercise both
Test(matrix4_rotation_float) {
	using vec3f = vector3d<float>;
	constexpr float degf = float(pi) / 180.0f;

	auto const transform_of = [] (vec3f const& e) {
		vector3d<radians<float>> const angles{
			radians<float>{e[0]}, radians<float>{e[1]}, radians<float>{e[2]}
		};
		return make_transform( vec3f{}, matrix_from_euler(angles) );
	};

	Checks {
		vec3f const euler{ 45*degf, 30*degf, 15*degf };
		auto const got = rotation_unscaled( transform_of(euler) );
		TestEqual( transform_of(got), transform_of(euler) );
	}

	Checks {
		// just short of the pole: must still take the general path
		vec3f const near_pole{ 40*degf, 89.9f*degf, -25*degf };
		auto const got = rotation_unscaled( transform_of(near_pole) );
		TestEqual( transform_of(got), transform_of(near_pole) );
	}
}

//! at |yaw| = 90° the decomposition differs, but must rebuild the matrix
Test(matrix4_rotation_gimbal_lock) {
	for (double sign : {1.0, -1.0}) {
		Checks {
			vec3 const euler{ 40*deg, sign * 90*deg, -25*deg };
			auto const mat = rotation_transform(euler);
			auto const got = rotation_unscaled(mat);
			TestEqual( rotation_transform(got), mat );
		}
	}
}

//! the scale is carried by the rows, and must divide back out
Test(matrix4_rotation_scaled) {
	vec3 const euler{ 45*deg, 30*deg, 15*deg };
	vec3 const scale{ 2, 3, 4 };

	auto mat = rotation_transform(euler);
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			mat.get(i, j) *= scale[i];

	Preconditions {
		TestEqual( scale_positive(mat), scale );
	}

	Checks {
		TestEqual( rotation(mat, scale), euler );
	}

	Checks {
		// the one-argument overload has to work out the scale itself
		TestEqual( rotation(mat), euler );
	}
}
} // namespace math
} // namespace aw
