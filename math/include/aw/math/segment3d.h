/*
 * Copyright (C) 2014-2026 Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_segment3d_h
#define aw_math_segment3d_h
#include <aw/math/vector3d.h>
namespace aw::math {
//! Represents a line segment in 3D space
template<typename T>
struct segment3d {
	//! Construct a degenerate segment at the origin
	constexpr segment3d() = default;

	//! Construct a line segment by individual components
	constexpr segment3d(T ax, T ay, T az, T bx, T by, T bz)
		: start{ax, ay, az}, end{bx, by, bz}
	{
	}

	//! Construct a line segment from start and end vectors
	constexpr segment3d(vector3d<T> const& start, vector3d<T> const& end)
		: start(start), end(end)
	{
	}

	//! Vector pointing from \a start to \a end
	constexpr vector3d<T> to_vector() const
	{
		return end - start;
	}

	//! Get unit vector pointing from \a start to \a end
	vector3d<T> direction() const
	{
		return normalize(to_vector());
	}

	//! Length of the line segment
	T length() const
	{
		return distance(start, end);
	}

	//! Squared length of the segment, avoids computing a square root
	constexpr T length_sq() const
	{
		return distance_sq(start, end);
	}

	/*!
	 * Project \a point onto the infinite line passing through
	 * \a start and \a end.
	 */
	vector3d<T> normal_point(vector3d<T> const& point) const
	{
		vector3d<T> const dir = direction();
		vector3d<T> const rel = point - start;

		return start + dir * dot(rel, dir);
	}

	/*!
	 * Find the point of the segment which is nearest to \a point.
	 *
	 * Unlike normal_point(), the result is clamped to the segment:
	 * projections falling beyond either end return that end.
	 */
	vector3d<T> closest_point(vector3d<T> const& point) const
	{
		vector3d<T> const vec = to_vector();

		T const len = vec.length();
		if (len == T(0))
			return start;

		vector3d<T> const dir = vec / len;

		T const projection = dot(point - start, dir);

		if (projection < T(0))
			return start;
		if (projection > len)
			return end;

		return start + dir * projection;
	}

	vector3d<T> start = {};
	vector3d<T> end   = {};
};
} // namespace aw::math
#endif//aw_math_segment3d_h
