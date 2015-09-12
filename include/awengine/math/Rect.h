/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Rect_
#define _awrts_Rect_
#include <awengine/common/types.h>
#include <awengine/math/Vector2d.h>

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


	T getWidth() const
	{
		return upperLeft.x() - lowerRight.x();
	}

	T getHeight() const
	{
		return upperLeft.y() - lowerRight.y();
	}

	Vector2d<T> getUpperLeft() const
	{
		return upperLeft;
	}

	Vector2d<T> getLowerRight() const
	{
		return lowerRight;
	}

	void setHeight(T height)
	{
		lowerRight.y() = height + upperLeft.y();
	}

	void setWidth(T width)
	{
		lowerRight.y() = width + upperLeft.x();
	}
	
	void setPosition(Vector2d<T> position)
	{
		lowerRight = position - upperLeft;
		upperLeft = position;
	}

	//! Coordinates of upper left corner
	Vector2d<T> upperLeft;
	//! Coordinates of lower right corner
	Vector2d<T> lowerRight;

};

/*!
 * Check if point is inside a rectangle.
 * \param point
 *      Point to test against.
 * \return
 *      true if point is within the rectangle,
 *      false otherwise
 */
template <typename T>
bool pointWithinRect(Vector2d<T> point, Rect<T> rect)
{
	bool isInside = (rect.upperLeft[0] <= point[0]  &&
			 rect.upperLeft[1] <= point[1]  &&
			 point[0] <= rect.lowerRight[0] &&
			 point[1] <= rect.lowerRight[1]);
	return isInside;
}
} // namespace awrts
#endif//_awrts_Rect_
