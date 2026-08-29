#include <aw/test/test.h>
#include <aw/math/quaternion.h>
#include <aw/math/matrix3.h>
#include <aw/math/vector_compare.h>
#include <aw/math/matrix_compare.h>
#include <aw/string/to_string/math/vector.h>
#include <aw/string/to_string/math/matrix.h>
#include <aw/types/traits/basic_traits.h>
#include <algorithm>

TestFile("math::quaternion");

namespace aw {
namespace math {
// Kept trivially copyable; see the note in vector.c++
static_assert(is_trivially_copyable<quaternion<float>>);
static_assert(std::is_standard_layout_v<quaternion<float>>);

namespace {
using quat = quaternion<double>;
using vec3 = vector3d<double>;

constexpr double deg = pi / 180.0;

//! Rotation matrix equivalent to \a q, built column by column
matrix3<double> as_matrix(quat const& q)
{
	auto const x = rotate(q, vec3{1, 0, 0});
	auto const y = rotate(q, vec3{0, 1, 0});
	auto const z = rotate(q, vec3{0, 0, 1});

	return {{ {x[0], y[0], z[0]},
	          {x[1], y[1], z[1]},
	          {x[2], y[2], z[2]} }};
}

vector3d<radians<double>> as_angles(vec3 const& v)
{
	return { radians<double>{v[0]}, radians<double>{v[1]}, radians<double>{v[2]} };
}
} // namespace

Test(quaternion_copy_assignment) {
	quat src {0.5, 0.5, 0.5, 0.5};
	quat dst;

	Checks {
		dst = src;

		TestEqual(dst.w, src.w);
		TestEqual(dst.x, src.x);
		TestEqual(dst.y, src.y);
		TestEqual(dst.z, src.z);
	}

	Postconditions {
		src = quat{1, 0, 0, 0};
		TestEqual(dst.w, 0.5);
		TestEqual(dst.x, 0.5);
	}
}

/*
 * Euler angles must name the same axes as matrix3: pitch is the
 * rotation around X, yaw around Y, roll around Z.
 */
Test(quaternion_euler_axes) {
	Checks {
		auto const p = quat::from_euler( 30*deg, 0, 0 );
		TestEqual( as_matrix(p), pitch_matrix( degrees<double>{30} ) );
	}

	Checks {
		auto const y = quat::from_euler( 0, 30*deg, 0 );
		TestEqual( as_matrix(y), yaw_matrix( degrees<double>{30} ) );
	}

	Checks {
		auto const r = quat::from_euler( 0, 0, 30*deg );
		TestEqual( as_matrix(r), roll_matrix( degrees<double>{30} ) );
	}
}

/*
 * ...and compose them in the same order, so that from_euler agrees
 * with matrix_from_euler for every combination.
 */
Test(quaternion_euler_order) {
	vec3 const e{ 45*deg, 30*deg, 15*deg };

	Checks {
		auto const q = quat::from_euler( e[0], e[1], e[2] );
		TestEqual( as_matrix(q), matrix_from_euler( as_angles(e) ) );
	}

	Checks {
		auto const q = quat::from_euler( e[0], e[1], e[2] );
		auto const m = roll_matrix ( radians<double>{e[2]} )
		             * yaw_matrix  ( radians<double>{e[1]} )
		             * pitch_matrix( radians<double>{e[0]} );
		TestEqual( as_matrix(q), m );
	}
}

//! `a * b` must compose in the same order as the matrix product `A * B`
Test(quaternion_multiplication_order) {
	auto const a = quat::from_euler( 45*deg, 0, 0 );
	auto const b = quat::from_euler( 0, 30*deg, 0 );

	Checks {
		TestEqual( as_matrix(a * b), as_matrix(a) * as_matrix(b) );
	}

	Checks {
		// applying b first, then a, must match rotating a vector twice
		vec3 const v{ 1, 2, 3 };
		TestEqual( rotate(a * b, v), rotate(a, rotate(b, v)) );
	}
}

//! to_euler is the inverse of from_euler, and uses the same layout
Test(quaternion_to_euler) {
	Checks {
		vec3 const e{ 45*deg, 30*deg, 15*deg };
		auto const q = quat::from_euler( e[0], e[1], e[2] );
		TestEqual( q.to_euler(), e );
	}

	// gimbal lock: pitch and roll are not individually defined at
	// yaw = ±90°, but the rotation must still be reproduced exactly
	for (double sign : {1.0, -1.0}) {
		Checks {
			auto const q = quat::from_euler( 40*deg, sign * 90*deg, -25*deg );
			auto const e = q.to_euler();
			auto const r = quat::from_euler( e[0], e[1], e[2] );
			TestEqual( as_matrix(r), as_matrix(q) );
		}
	}
}

//! matrix3::to_quaternion must invert the conversion above
Test(quaternion_from_matrix) {
	vec3 const e{ 45*deg, 30*deg, 15*deg };
	auto const q = quat::from_euler( e[0], e[1], e[2] );

	Checks {
		auto const m = matrix_from_euler( as_angles(e) );
		TestEqual( as_matrix( to_quaternion(m) ), as_matrix(q) );
	}
}

Test(quaternion_axis_angle) {
	Checks {
		auto const q = quat::from_axis_angle( vec3{0, 1, 0}, 30*deg );
		TestEqual( as_matrix(q), yaw_matrix( degrees<double>{30} ) );
	}

	Checks {
		auto const q = quat::from_axis_angle( vec3{0, 0, 2}, 40*deg );
		auto const aa = q.to_axis_angle();
		TestEqual( aa.axis, vec3{0, 0, 1} );
		TestEqual( aa.angle, 40*deg );
	}

	Checks {
		// matrix_from_axis_angle expects a unit axis, set_axis_angle
		// normalizes for you -- feed both the same normalized vector
		auto const axis = normalize( vec3{1, 2, 3} );

		auto const m = matrix_from_axis_angle( axis, radians<double>{40*deg} );
		auto const q = quat::from_axis_angle( axis, 40*deg );
		TestEqual( as_matrix(q), m );
	}
}

Test(quaternion_rotate) {
	Checks {
		// same rotation the matrix3_rotation test checks
		auto const q = quat::from_euler( 0, 90*deg, 0 );
		TestEqual( rotate(q, vec3{1, 0, 0}), vec3{0, 0, -1} );
	}

	Checks {
		auto const q = quat::from_euler( 45*deg, 30*deg, 15*deg );
		TestEqual( rotate(conjugate(q), rotate(q, vec3{1, 2, 3})),
		           vec3{1, 2, 3} );
	}
}

Test(quaternion_interpolation) {
	auto const a = quat::from_euler( 0, 0, 0 );
	auto const b = quat::from_euler( 0, 90*deg, 0 );

	Checks {
		TestEqual( as_matrix( slerp(a, b, 0.0, true) ), as_matrix(a) );
		TestEqual( as_matrix( slerp(a, b, 1.0, true) ), as_matrix(b) );
		TestEqual( as_matrix( slerp(a, b, 0.5, true) ),
		           as_matrix( quat::from_euler( 0, 45*deg, 0 ) ) );
	}

	Checks {
		TestEqual( as_matrix( nlerp(a, b, 0.0) ), as_matrix(a) );
		TestEqual( as_matrix( nlerp(a, b, 1.0) ), as_matrix(b) );
	}
}
} // namespace math
} // namespace aw
