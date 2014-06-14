#ifndef __H_INCLUDED__AWRTS_CUnitType
#define __H_INCLUDED__AWRTS_CUnitType

#include <hrengin/common/hrTypes.h>

namespace awrts
{

struct UnitType
{
	hrengin::u32 id;

	char * textUnitName;
	
	char * visualModelName;

	hrengin::u32 guiSelectionShapeId;

	hrengin::u32 statsHitPointsMax;
	
	enum UnitMovementType
	{
		UM_STATIC = 0,
		UM_GROUND,
		UM_SWIMMING,
		UM_AMPHIBIOUS,
		UM_HOVER,
		UM_HOVER_AMPHIBIOUS,
		UM_AIRBORNE
	} movementType;
	hrengin::f32 movementHeight;
	hrengin::f32 movementSpeed;
	hrengin::f32 movementAcceleration;
	hrengin::f32 movementTurnSpeed;
	hrengin::f32 movementRequiredWidth;
	hrengin::f32 movementTurnRadius;
};

}

#endif//__H_INCLUDED__AWRTS_CUnitType