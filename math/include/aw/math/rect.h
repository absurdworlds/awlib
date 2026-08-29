/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_rect_h
#define aw_math_rect_h
#include <aw/math/vector2d.h>
namespace aw::math {
/*!
 * Represents a 2D rectangle, used mostly for GUI rendering.
 *
 * \note Coordinates follow the screen convention: the Y axis grows
 *       downwards, so a rectangle is well-formed when \a lower_right
 *       is component-wise greater than \a upper_left.
 */
template<typename T>
struct rect {
	//! Construct zero-sized rect at (0,0)
	constexpr rect() = default;

	//! Construct specifying each coordinate
	constexpr rect(T x, T y, T x2, T y2)
		: upper_left{x,y}, lower_right{x2,y2}
	{
	}

	//! Construct specifying coordinates as vectors
	constexpr rect(vector2d<T> const& upper_left, vector2d<T> const& lower_right)
		: upper_left(upper_left), lower_right(lower_right)
	{
	}

	constexpr rect& operator+=(rect const& other)
	{
		upper_left  += other.upper_left;
		lower_right += other.lower_right;
		return *this;
	}

	constexpr rect& operator-=(rect const& other)
	{
		upper_left  -= other.upper_left;
		lower_right -= other.lower_right;
		return *this;
	}

	constexpr rect& operator+=(vector2d<T> const& vec)
	{
		upper_left  += vec;
		lower_right += vec;
		return *this;
	}

	constexpr rect& operator-=(vector2d<T> const& vec)
	{
		upper_left  -= vec;
		lower_right -= vec;
		return *this;
	}

	//! Distance between the left and the right edges
	constexpr T width() const
	{
		return lower_right.x() - upper_left.x();
	}

	//! Distance between the top and the bottom edges
	constexpr T height() const
	{
		return lower_right.y() - upper_left.y();
	}

	//! Get center of the rectangle.
	constexpr vector2d<T> center() const
	{
		return (upper_left + lower_right) / T(2);
	}

	//! Move the right edge, keeping the left one in place
	constexpr void set_width(T width)
	{
		lower_right.x() = upper_left.x() + width;
	}

	//! Move the bottom edge, keeping the top one in place
	constexpr void set_height(T height)
	{
		lower_right.y() = upper_left.y() + height;
	}

	//! Move the rectangle, preserving its size
	constexpr void set_position(vector2d<T> const& position)
	{
		lower_right += position - upper_left;
		upper_left   = position;
	}

	//! Coordinates of upper left corner
	vector2d<T> upper_left  = {};
	//! Coordinates of lower right corner
	vector2d<T> lower_right = {};
};

//! Sum of two rectangles
template<typename T>
constexpr rect<T> operator+(rect<T> a, rect<T> const& b)
{
	a += b;
	return a;
}

//! Difference of two rectangles
template<typename T>
constexpr rect<T> operator-(rect<T> a, rect<T> const& b)
{
	a -= b;
	return a;
}

/*!
 * Check if point is inside a rectangle.
 * \param point
 *      Point to test against.
 * \return
 *      true if point is within the rectangle,
 *      false otherwise
 */
template<typename T>
constexpr bool contains(rect<T> const& rect, vector2d<T> const& point)
{
	return rect.upper_left.x()  <= point.x() &&
	       rect.upper_left.y()  <= point.y() &&
	       point.x() <= rect.lower_right.x() &&
	       point.y() <= rect.lower_right.y();
}
} // namespace aw::math
#endif//aw_math_rect_h
