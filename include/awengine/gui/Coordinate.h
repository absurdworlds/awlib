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
		                  offset + other.offset);
	}
	Coordinate operator -(Coordinate const& other) const
	{
		return Coordinate(fraction - other.fraction,
		                  offset - other.offset);
	}
	Coordinate operator *(Coordinate const& other) const
	{
		return Coordinate(fraction * other.fraction,
		                  offset * other.offset);
	}
	Coordinate operator /(Coordinate const& other) const
	{
		return Coordinate(fraction / other.fraction,
		                  offset / other.offset);
	}
	Coordinate operator +(i32 v) const
	{
		return Coordinate(fraction,
		                  offset + v);
	}
	Coordinate operator -(i32 v) const
	{
		return Coordinate(fraction,
		                  offset - v);
	}

	Coordinate& operator +=(Coordinate const& other)
	{
		fraction += other.fraction;
		offset += other.offset;
		return *this;
	}
	Coordinate& operator -=(Coordinate const& other)
	{
		fraction -= other.fraction;
		offset -= other.offset;
		return *this;
	}
	Coordinate& operator *=(Coordinate const& other)
	{
		fraction *= other.fraction;
		offset *= other.offset;
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

} // namespace gui
} // namespace awrts
#endif//_awrts_gui_Coordinate_
