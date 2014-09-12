/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_NavigatorUtils_
#define _hrengin_NavigatorUtils_

#include <hrengin/common/types.h>
#include <hrengin/common/math.h>

namespace hrengin {
namespace ai {

/* Check if turn can be accomplished */
bool isValidTurn(f32 speed, f32 turnRate, f32 angle, f32 distance)
{
	f32 radius = speed / turnRate;
	f32 chord = 2*radius*abs(sin(angle));
	return distance > chord;
}

} // namespace ai
} // namespace hrengin

#endif //_hrengin_NavigatorUtils_
