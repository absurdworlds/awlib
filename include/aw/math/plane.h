/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_plane_h
#define aw_math_plane_h
#include <aw/math/vector3d.h>
#include <aw/math/equals.h>

namespace aw {
namespace math {

enum class relation {
	front,
	back,
	planar
};


//! Plane in three-dimensional space
template<typename T>
struct plane {
	plane(vector3d<T> const& point, vector3d<T> const& normal)
		: _normal{ normal.normalize() }
	{
		compute_distance(point);
	}

	plane(vector3d<T> const& a, vector3d<T> const& b, vector3d<T> const& c)
	{
		_normal = cross(b - a, c - a).normalize();
		compute_distance(a);
	}

	void compute_distance(vector3d<T> const& point)
	{
		_distance = -dot(point, _normal);
	}

	//! Calculate distance to a point.
	T distance_to_point(vector3d<T> const& point) const
	{
		return dot(point, _normal) + _distance;
	}

	//! Get normal vector of the plane.
	vector3d<T> normal() const
	{
		return _normal;
	}

	relation classify_point(vector3d<T> const& point) const
	{
		constexpr T zero = T(0);
		const     T dist = distance_to_point(point);

		if ( equals(dist, zero) )
			return relation::planar;
		return dist < zero ? relation::back : relation::front;
	}


private:
	//! Unit normal
	vector3d<T> _normal;
	//! Distance from the origin
	T           _distance;
};
} // namespace math
} // namespace aw
#endif//aw_math_plane_h
