/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_Coordinate_
#define _awrts_gui_Coordinate_
#include <awengine/math/Rect.h>

namespace awrts {
namespace gui {

struct Coordinate {
	Coordinate(f32 fraction)
		: fraction(fraction), offset(0)
	{}
	Coordinate(f64 fraction)
		: fraction(fraction), offset(0)
	{}
	Coordinate(i32 offset)
		: fraction(0.0), offset(offset)
	{}
	Coordinate(f32 fraction, i32 offset)
		: fraction(fraction), offset(offset)
	{}

	Coordinate operator +(Coordinate const& other) const
	{
		return Coordinate(fraction + other.fraction,
		                  offset   + other.offset);
	}
	Coordinate operator -(Coordinate const& other) const
	{
		return Coordinate(fraction - other.fraction,
		                  offset   - other.offset);
	}
	Coordinate operator *(Coordinate const& other) const
	{
		return Coordinate(fraction * other.fraction,
		                  offset   * other.offset);
	}
	Coordinate operator /(Coordinate const& other) const
	{
		return Coordinate(fraction / other.fraction,
		                  offset   / other.offset);
	}

	Coordinate operator + (i32 v) const
	{
		return Coordinate(fraction,
		                  offset + v);
	}
	Coordinate operator - (i32 v) const
	{
		return Coordinate(fraction,
		                  offset - v);
	}

	Coordinate& operator +=(Coordinate const& other)
	{
		fraction += other.fraction;
		offset   += other.offset;
		return *this;
	}
	Coordinate& operator -=(Coordinate const& other)
	{
		fraction -= other.fraction;
		offset   -= other.offset;
		return *this;
	}
	Coordinate& operator *=(Coordinate const& other)
	{
		fraction *= other.fraction;
		offset   *= other.offset;
		return *this;
	}
	Coordinate& operator /=(Coordinate const& other)
	{
		fraction /= other.fraction;
		offset /= other.offset;
		return *this;
	}
	Coordinate& operator +=(i32 v)
	{
		offset += v;
		return *this;
	}
	Coordinate& operator -=(i32 v)
	{
		offset -= v;
		return *this;
	}

	/*!
	 * Fraction of a parent element's size
	 */
	f32 fraction;
	/*!
	 * Offset in pixels, applied after calculating
	 * the fraction
	 */
	f32 offset;
};

inline Rect<i32> toPixels(Rect<Coordinate> const& rect,
                          Vector2d<i32> const& screen)
{
	Rect<i32> tmp;
	tmp.upperLeft.x()  = rect.upperLeft.x().fraction * screen.x();
	tmp.upperLeft.x() += rect.upperLeft.x().offset;
	tmp.upperLeft.y()  = rect.upperLeft.y().fraction * screen.y();
	tmp.upperLeft.y() += rect.upperLeft.y().offset;
	tmp.lowerRight.x()  = rect.lowerRight.x().fraction * screen.x();
	tmp.lowerRight.x() += rect.lowerRight.x().offset;
	tmp.lowerRight.y()  = rect.lowerRight.y().fraction * screen.y();
	tmp.lowerRight.y() += rect.lowerRight.y().offset;
	return tmp;
}

} // namespace gui
} // namespace awrts
#endif//_awrts_gui_Coordinate_
