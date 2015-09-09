/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_ToIrr_Color__
#define awrts_ToIrr_Color__
#include <Irrlicht/rect.h>
#include <awengine/math/Rect.h>

namespace awrts {
irr::video::SColor toIrr(graphics::Color color)
{
	return irr::video::SColor(color.a(), color.r(), color.g(), color.b());
}
} // namespace awrts
#endif //awrts_ToIrr_Color__
