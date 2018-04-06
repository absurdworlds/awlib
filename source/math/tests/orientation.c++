#include <aw/utility/test.h>
#include <aw/math/orientation.h>
#include <aw/math/vector_compare.h>
#include <aw/math/matrix_compare.h>
#include <aw/utility/to_string/math/matrix.h>

#include <algorithm>

TestFile("math::orientation");

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

Test(look_at) {
	using vec3 = math::vector3d<double>;
	Checks {
		auto look = look_at(vec3{0,0,-1} );
		auto rot  = yaw_matrix( degrees<double>{ 0 } );
		TestEqual( look, rot );
	}

	Checks {
		auto look = look_at( vec3{-1,0,0} );
		auto rot  = yaw_matrix( degrees<double>{ 90 } );
		TestEqual( look, rot );
	}

	Checks {
		auto look = look_at( vec3{0,0,1} );
		auto rot  = yaw_matrix( degrees<double>{ 180 } );
		TestEqual( look, rot );
	}

	Checks {
		auto look = look_at( vec3{1,0,0} );
		auto rot  = yaw_matrix( degrees<double>{ 270 } );
		TestEqual( look, rot );
	}

	/*Checks {
		auto look = look_at( vec3{0,1,0} );
		auto rot  = pitch_matrix( degrees<double>{ 90 } );
		TestEqual( look, rot );
	}*/
};

} // namespace math
} // namespace aw
