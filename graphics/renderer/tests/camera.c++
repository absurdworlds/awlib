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

//! Where a point \a distance units in front of the camera lands on the depth axis
float ndc_depth( math::matrix4<f32> const& m, float distance )
{
	// the camera looks down -z, and clip coordinates are divided by w
	float z = -distance;
	float clip_z = m.get(2,2) * z + m.get(2,3);
	float clip_w = m.get(3,2) * z + m.get(3,3);
	return clip_z / clip_w;
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

Test(camera_out_of_the_box_has_a_view_volume) {
	camera cam;

	auto& m = cam.projection_matrix();

	Checks {
		// the nearer of two points has to come out in front of the farther one
		TestAssert( ndc_depth(m, 1.0f) < ndc_depth(m, 2.0f) );
	}
}

Test(camera_maps_its_clip_planes_onto_the_depth_range) {
	constexpr float near_z = 0.5f;
	constexpr float far_z  = 100.0f;

	camera cam;
	cam.set_near_z( near_z );
	cam.set_far_z( far_z );

	auto& m = cam.projection_matrix();

	Checks {
		TestAssert( math::equals( ndc_depth(m, near_z), -1.0f ) );
		TestAssert( math::equals( ndc_depth(m, far_z),   1.0f ) );
	}
}
} // namespace aw::gl3
