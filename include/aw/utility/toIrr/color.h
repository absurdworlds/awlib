/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_ToIrr_Color__
#define aw_ToIrr_Color__
#include <Irrlicht/SColor.h>
#include <aw/graphics/Color.h>

namespace aw {
irr::video::SColor toIrr(graphics::Color color)
{
	return irr::video::SColor(color.a(), color.r(), color.g(), color.b());
}

graphics::Color toAW(irr::video::SColor color)
{
	return graphics::Color(color.getAlpha(), color.getRed(),
	                       color.getGreen(), color.getBlue());
}
} // namespace aw
#endif //aw_ToIrr_Color__
