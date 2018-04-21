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

Test(look_at_inverse)
{
	using vec3 = math::vector3d<double>;
	Checks {
		auto look = look_at_inverse( vec3{-1,0,0} );
		auto rot  = yaw_matrix( degrees<double>{ 90 } );
		TestEqual( look, transpose( rot ) );
	}

	Checks {
		vec3 pos{1,0,0};
		auto rot = yaw_matrix( degrees<double>{ 90 } );
		//--------------------
		auto M_r = expand_matrix( rot );
		auto M_t = identity_matrix<double, 4>;
		M_t[0][3] = -pos[0];
		M_t[1][3] = -pos[1];
		M_t[2][3] = -pos[2];
		auto trf = transpose( M_r ) * M_t;
		//--------------------
		auto look = look_at_inverse( pos, vec3{0,0,0}, vec3{0,1,0} );
		//--------------------
		TestEqual( look, trf );
	}
}

} // namespace math
} // namespace aw
