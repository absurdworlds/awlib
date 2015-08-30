/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Rect_
#define _awrts_Rect_

#include <awrts/common/types.h>
#include <awrts/math/Vector2d.h>

namespace awrts {
//! Represents a 2D rectangle, used mostly for GUI rendering
template <class T>
class Rect {
public:
	//! Construct zero-sized rect at (0,0)
	Rect()
		: upperLeft(0,0), lowerRight(0,0)
	{
	}

	//! Construct specifying each coordinate
	Rect(T x, T y, T x2, T y2)
		: upperLeft(x,y), lowerRight(x2,y2)
	{
	}

	//! Construct specifying coordinates as vectors
	Rect(const Vector2d<T>& upperLeft, const Vector2d<T>& lowerRight)
		: upperLeft(upperLeft), lowerRight(lowerRight)
	{
	}

	//! Coordinates of upper left corner
	Vector2d<T> upperLeft;
	//! Coordinates of lower right corner
	Vector2d<T> lowerRight;

};

} // namespace awrts
#endif//_awrts_Rect_
