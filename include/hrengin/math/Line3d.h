/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Line3d_
#define _hrengin_Line3d_

#include <hrengin/math/Vector3d.h>

namespace hrengin {
//! Represents a line segment in 3D space
template<typename T>
class Segment3d {
public:
	//! Default constructor
	Segment3d()
		: start(0, 0, 0), end(0, 0, 0)
	{
	}

	//! Construct line by individual components
	Segment3d(T ax, T ay, T az, T bx, T by, T bz)
		: start(ax, ay, az), end(bx, by, bz)
	{
	}

	//! Construct line from start and end vectors
	Segment3d(Vector3d<T> const& start, Vector3d<T> const& end)
		: start(start), end(end)
	{
	}

	//! Assignment operator
	Segment3d<T>& operator = (Segment3d<T> const& line)
	{
		start = line.start;
		end = line.end;

		return *this;
	}

	Vector3d<T> getNormalPoint(Vector3d<T> const& point) const
	{
		Vector3d<T> a = direction();
		Vector3d<T> b = point - start;

		a.normalize();

		T projectionLength = b.dot(a);

		return start + a * projectionLength;
	}
	
	Vector3d<T> getClosestPoint(Vector3d<T> const& point) const
	{
		Vector3d<T> a = vector();
		Vector3d<T> b = point - start;

		T length = a.length();
		a /= length;

		T projectionLength = b.dot(a);

		if(projectionLength < 0) {
			return start;
		} else if(projectionLength > length) {
			return end;
		}

		return start + a * length;
	}

	Vector3d<T> vector() const
	{
		return end - start;
	}

	//! Get direction vector
	Vector3d<T> direction() const
	{
		return vector().normalized();
	}

	Vector3d<T> length() const
	{
		return start.getDistance(end);
	}

public:
	Vector3d<T> start;
	Vector3d<T> end;
};

/*! Alias for Segment3d */
template<typename T>
using Line3d = Segment3d<T>;


} // namespace hrengin
#endif// _hrengin_Line3d_
