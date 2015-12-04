/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_NavigatorUtils_
#define _aw_NavigatorUtils_

#include <aw/common/types.h>
#include <aw/common/math.h>

namespace aw {
namespace ai {

/* Check if turn can be accomplished */
inline bool isValidTurn(f32 speed, f32 turnRate, f32 angle, f32 distance)
{
	f32 radius = speed / math::degToRad(turnRate);
	f32 chord = 2*radius*abs(sin(math::degToRad( angle )));
	return distance > chord;
}

inline f32 getMaxTurnAngle(f32 speed, f32 turnRate, f32 distance)
{
	f32 angle = asin(distance * math::degToRad(turnRate) / (2 * speed));
	return math::radToDeg(angle);
}

} // namespace ai
} // namespace aw
#endif //_aw_NavigatorUtils_
