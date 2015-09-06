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
	Coordinate(f32 fraction, i32 offset)
		: fraction(fraction), offset(offset)
	{}

	/*!
	 * Fraction of a parent element's size
	 */
	f32 fraction;
	/*!
	 * Offset in pixels, applied after calculating
	 * the fraction
	 */
	f32 offset;

	Coordinate operator+(Coordinate const& other) const
	{
		return Coordinate(fraction + other.fraction,
			       	  offset + other.offset);
	}
	Coordinate operator-(Coordinate const& other) const
	{
		return Coordinate(fraction - other.fraction,
			       	  offset - other.offset);
	}
	Coordinate operator*(Coordinate const& other) const
	{
		return Coordinate(fraction * other.fraction,
			       	  offset * other.offset);
	}
	Coordinate operator/(Coordinate const& other) const
	{
		return Coordinate(fraction / other.fraction,
			       	  offset / other.offset);
	}
}

} // namespace gui
} // namespace awrts
#endif//_awrts_gui_Coordinate_
