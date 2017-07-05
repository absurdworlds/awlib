/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_camera_h
#define aw_graphics_gl3_camera_h
#include <aw/math/matrix4.h>
#include <aw/math/angle.h>
#include <aw/math/math.h>
namespace aw {
namespace gl3 {
struct camera {
	camera()
	{
		math::set_identity(perspective);
	}

	void set_far_z(float value)
	{
		zfar = value;
		recalc_planes();
	}

	void set_near_z(float value)
	{
		znear = value;
		recalc_planes();
	}

	void set_fov(math::radians<float> value)
	{
		frustum_scale = calc_frustum_scale( value );
		perspective.get(0,0) = frustum_scale / aspect;
		perspective.get(1,1) = frustum_scale;
	}

	void set_aspect_ratio(float value)
	{
		aspect = value;
		perspective.get(0,0) = frustum_scale / aspect;
	}

	math::matrix4<f32> const& projection_matrix() const
	{
		/*projmat = {
			s, 0, 0, 0,
			0, s, 0, 0,
			0, 0, z, w,
			0, 0, -1, 0,
		};*/
		return perspective;
	}

protected:
	static constexpr auto default_fov = math::degrees<float>{45};
	static float calc_frustum_scale( math::angle<float> fov )
	{
		return math::cot(fov / 2.0f);
	}

	void recalc_planes()
	{
		float zz = (zfar + znear) / (znear - zfar);
		float zw = 2 * zfar * znear / (znear - zfar);

		perspective.get(2,2) = zz;
		perspective.get(2,3) = zw;
		perspective.get(3,2) = -1;
		perspective.get(3,3) = 0;
	}

private:
	float frustum_scale = calc_frustum_scale( default_fov );
	float aspect = 1.0f;
	float zfar   = 1.0f;
	float znear  = 2.0f;

	math::matrix4<f32> perspective;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_camera_h
