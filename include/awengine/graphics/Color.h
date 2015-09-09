/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Color_
#define _awrts_Color_
#include <awengine/math/Vector4d.h>

namespace awrts {
namespace graphics {
class Color {
public:
	Color(u8 r, u8 g, u8 b)
		: value((u32(r) << 16) + 
		        (u32(g) << 8) +
		        (u32(b)))
	{
	}

	Color(u8 a, u8 r, u8 g, u8 b)
		: value((u32(a) << 24) + (u32(r) << 16) + 
		        (u32(g) << 8) + u32(b))
	{
	}

	Color(u32 value)
		: value(value)
	{
	}

	u32 getAlpha() const
	{
		return (value >> 24) & 0xFF;
	}

	u32 getRed() const
	{
		return (value >> 16) & 0xFF;
	}

	u32 getGreen() const
	{
		return (value >> 8) & 0xFF;
	}

	u32 getBlue() const
	{
		return (value) & 0xFF;
	}
	
	u32 a() const
	{
		return getAlpha();
	}

	u32 r() const
	{
		return getRed();
	}

	u32 g() const
	{
		return getGreen();
	}

	u32 b() const
	{
		return getBlue();
	}

	u32 getARGB() const
	{
		return value;
	}
private:
	u32 value;
};

inline Color darken(Color const& color, u8 val)
{
	u32 red = color.getRed() * (0xFF - val) / 0xFF;
	u32 green = color.getGreen() * (0xFF - val) / 0xFF;
	u32 blue = color.getBlue() * (0xFF - val) / 0xFF;
	return Color(color.getAlpha(), red, green, blue);
}

} // namespace graphics
} // namespace awrts
#endif//_awrts_Color_
