/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_ToIrr_Rect__
#define aw_ToIrr_Rect__
#include <Irrlicht/rect.h>
#include <aw/math/Rect.h>

namespace aw {
irr::core::rect<irr::f32> toIrr(Rect<f32> awRect)
{
	return irr::core::rect<irr::f32>(
	       awRect.upperLeft.x(), awRect.upperLeft.y(),
	       awRect.lowerRight.x(), awRect.lowerRight.y());
}
irr::core::rect<irr::s32> toIrr(Rect<i32> awRect)
{
	return irr::core::rect<irr::s32>(
	       awRect.upperLeft.x(),  awRect.upperLeft.y(),
	       awRect.lowerRight.x(), awRect.lowerRight.y());
}
} // namespace aw
#endif //aw_ToIrr_Rect__
