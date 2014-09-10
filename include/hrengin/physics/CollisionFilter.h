/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CollisionFilter_
#define _hrengin_CollisionFilter_

#include <hrengin/common/types.h>
#include <hrengin/common/macro.h>

// temporary, should be user-defined
enum collisiontypes {
	COL_NOTHING = 0,
	COL_GROUND = BIT(0),
	COL_UNIT = BIT(1),
	COL_DEBRIS = BIT(2)
};

namespace hrengin {
namespace physics {

struct CollisionFilter {
	CollisionFilter(u16 colGroup, u16 bitMask)
		: group(colGroup), mask(bitMask)
	{
	}
	u16 group;
	u16 mask;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_CollisionFilter_
