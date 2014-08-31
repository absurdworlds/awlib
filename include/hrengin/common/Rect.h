#ifndef _hrengin_Rect_
#define _hrengin_Rect_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector2d.h>

namespace hrengin {

template <class T>
class Rect {
public:
	// Coordinates of upper left corner
	Vector2d<T> upperLeft_;
	// Coordinates of lower right corner
	Vector2d<T> lowerRight_;
public:
	/* Construct zero-sized rect at (0,0) */
	Rect() : upperLeft(0,0), lowerRight(0,0)
	{
	}

	/* Construct specifying each coordinate */
	Rect(T x, T y, T x2, T y2) : upperLeft_(x,y), lowerRight_(x2,y2)
	{
	}

	/* Construct specifying coordinates as vectors */
	Rect(const Vector2d<T>& upperLeft, const Vector2d<T>& lowerRight)
		: upperLeft_(upperLeft), lowerRight_(lowerRight)
	{
	}

	/* It's all borrowed from Irrlicht
	template <class U>
	rect(const Vector2d<T>& pos, const dimension2d<U>& size)
		: upperLeft_(pos), lowerRight(pos.X + size.Width, pos.Y + size.Height) {}

	//! move right by given numbers
	rect<T> operator + (const Vector2d<T>& pos) const
	{
		rect<T> ret(*this);
		return ret+=pos;
	}

	//! move right by given numbers
	rect<T>& operator+=(const Vector2d<T>& pos)
	{
		upperLeft_ += pos;
		lowerRight += pos;
		return *this;
	}

	//! move left by given numbers
	rect<T> operator-(const Vector2d<T>& pos) const
	{
		rect<T> ret(*this);
		return ret-=pos;
	}

	//! move left by given numbers
	rect<T>& operator-=(const Vector2d<T>& pos)
	{
		upperLeft_ -= pos;
		lowerRight -= pos;
		return *this;
	}

	//! equality operator
	bool operator==(const rect<T>& other) const
	{
		return (upperLeft_ == other.upperLeft_ &&
			lowerRight == other.lowerRight);
	}

	//! inequality operator
	bool operator!=(const rect<T>& other) const
	{
		return (upperLeft_ != other.upperLeft_ ||
			lowerRight != other.lowerRight);
	}

	//! compares size of rectangles
	bool operator<(const rect<T>& other) const
	{
		return getArea() < other.getArea();
	}

	//! Returns size of rectangle
	T getArea() const
	{
		return getWidth() * getHeight();
	}

	//! Returns if a 2d point is within this rectangle.
	//** \param pos Position to test if it lies within this rectangle.
	\return True if the position is within the rectangle, false if not. /
	bool isPointInside(const Vector2d<T>& pos) const
	{
		return (upperLeft_.X <= pos.X &&
			upperLeft_.Y <= pos.Y &&
			lowerRight.X >= pos.X &&
			lowerRight.Y >= pos.Y);
	}

	//! Check if the rectangle collides with another rectangle.
	//** \param other Rectangle to test collision with
	\return True if the rectangles collide. /
	bool isRectCollided(const rect<T>& other) const
	{
		return (lowerRight.Y > other.upperLeft_.Y &&
			upperLeft_.Y < other.lowerRight.Y &&
			lowerRight.X > other.upperLeft_.X &&
			upperLeft_.X < other.lowerRight.X);
	}

	//! Clips this rectangle with another one.
	//** \param other Rectangle to clip with /
	void clipAgainst(const rect<T>& other)
	{
		if (other.lowerRight.X < lowerRight.X)
			lowerRight.X = other.lowerRight.X;
		if (other.lowerRight.Y < lowerRight.Y)
			lowerRight.Y = other.lowerRight.Y;

		if (other.upperLeft_.X > upperLeft_.X)
			upperLeft_.X = other.upperLeft_.X;
		if (other.upperLeft_.Y > upperLeft_.Y)
			upperLeft_.Y = other.upperLeft_.Y;

		// correct possible invalid rect resulting from clipping
		if (upperLeft_.Y > lowerRight.Y)
			upperLeft_.Y = lowerRight.Y;
		if (upperLeft_.X > lowerRight.X)
			upperLeft_.X = lowerRight.X;
	}

	//! Moves this rectangle to fit inside another one.
	//** \return True on success, false if not possible /
	bool constrainTo(const rect<T>& other)
	{
		if (other.getWidth() < getWidth() || other.getHeight() < getHeight())
			return false;

		T diff = other.lowerRight.X - lowerRight.X;
		if (diff < 0)
		{
			lowerRight.X += diff;
			upperLeft_.X  += diff;
		}

		diff = other.lowerRight.Y - lowerRight.Y;
		if (diff < 0)
		{
			lowerRight.Y += diff;
			upperLeft_.Y  += diff;
		}

		diff = upperLeft_.X - other.upperLeft_.X;
		if (diff < 0)
		{
			upperLeft_.X  -= diff;
			lowerRight.X -= diff;
		}

		diff = upperLeft_.Y - other.upperLeft_.Y;
		if (diff < 0)
		{
			upperLeft_.Y  -= diff;
			lowerRight.Y -= diff;
		}

		return true;
	}

	//! Get width of rectangle.
	T getWidth() const
	{
		return lowerRight.X - upperLeft_.X;
	}

	//! Get height of rectangle.
	T getHeight() const
	{
		return lowerRight.Y - upperLeft_.Y;
	}

	//! If the lower right corner of the rect is smaller then the upper left, the points are swapped.
	void repair()
	{
		if (lowerRight.X < upperLeft_.X)
		{
			T t = lowerRight.X;
			lowerRight.X = upperLeft_.X;
			upperLeft_.X = t;
		}

		if (lowerRight.Y < upperLeft_.Y)
		{
			T t = lowerRight.Y;
			lowerRight.Y = upperLeft_.Y;
			upperLeft_.Y = t;
		}
	}

	//! Returns if the rect is valid to draw.
	//** It would be invalid if the upperLeft_ is lower or more
	right than the lowerRight. /
	bool isValid() const
	{
		return ((lowerRight.X >= upperLeft_.X) &&
			(lowerRight.Y >= upperLeft_.Y));
	}

	//! Get the center of the rectangle
	Vector2d<T> getCenter() const
	{
		return Vector2d<T>(
				(upperLeft_.X + lowerRight.X) / 2,
				(upperLeft_.Y + lowerRight.Y) / 2);
	}

	//! Get the dimensions of the rectangle
	dimension2d<T> getSize() const
	{
		return dimension2d<T>(getWidth(), getHeight());
	}


	//! Adds a point to the rectangle
	//** Causes the rectangle to grow bigger if point is outside of
	the box
	\param p Point to add to the box. /
	void addInternalPoint(const Vector2d<T>& p)
	{
		addInternalPoint(p.X, p.Y);
	}

	//! Adds a point to the bounding rectangle
	//** Causes the rectangle to grow bigger if point is outside of
	the box
	\param x X-Coordinate of the point to add to this box.
	\param y Y-Coordinate of the point to add to this box. /
	void addInternalPoint(T x, T y)
	{
		if (x>lowerRight.X)
			lowerRight.X = x;
		if (y>lowerRight.Y)
			lowerRight.Y = y;

		if (x<upperLeft_.X)
			upperLeft_.X = x;
		if (y<upperLeft_.Y)
			upperLeft_.Y = y;
	}
	*/
};

} // namespace hrengin

#endif//_hrengin_Rect_
