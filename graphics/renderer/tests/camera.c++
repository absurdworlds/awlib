/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/camera.h>

#include <aw/test/test.h>

#include <cmath>

TestFile( "graphics::gl3 camera" );

namespace aw::gl3 {
namespace {
//! Widescreen, so the two axes cannot be confused for one another
constexpr float aspect = 16.0f / 9.0f;

float horizontal_angle( math::matrix4<f32> const& m )
{
	return 2 * std::atan( 1.0f / m.get(0,0) );
}

float vertical_angle( math::matrix4<f32> const& m )
{
	return 2 * std::atan( 1.0f / m.get(1,1) );
}

float radians_in( math::degrees<float> angle )
{
	return math::radians<float>{angle}.count();
}
} // namespace

Test(camera_fov_is_the_horizontal_angle) {
	constexpr auto fov = math::degrees<float>{90};

	camera cam;
	cam.set_aspect_ratio( aspect );
	cam.set_fov( fov );

	auto& m = cam.projection_matrix();

	Checks {
		TestAssert( math::equals( horizontal_angle(m), radians_in(fov) ) );

		// a widescreen viewport spans less vertically than horizontally
		TestAssert( vertical_angle(m) < horizontal_angle(m) );
	}
}

Test(camera_vfov_is_the_vertical_angle) {
	constexpr auto fov = math::degrees<float>{60};

	camera cam;
	cam.set_aspect_ratio( aspect );
	cam.set_vfov( fov );

	auto& m = cam.projection_matrix();

	Checks {
		TestAssert( math::equals( vertical_angle(m), radians_in(fov) ) );
		TestAssert( horizontal_angle(m) > vertical_angle(m) );
	}
}

Test(camera_widening_the_viewport_keeps_the_vertical_angle) {
	constexpr auto fov = math::degrees<float>{60};

	camera cam;
	cam.set_aspect_ratio( aspect );
	cam.set_vfov( fov );

	auto before = horizontal_angle( cam.projection_matrix() );
	cam.set_aspect_ratio( 2 * aspect );
	auto after  = horizontal_angle( cam.projection_matrix() );

	Checks {
		// the extra width is shown, rather than the same image stretched
		TestAssert( math::equals( vertical_angle(cam.projection_matrix()), radians_in(fov) ) );
		TestAssert( after > before );
	}
}
} // namespace aw::gl3
