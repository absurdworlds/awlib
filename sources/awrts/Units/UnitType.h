#ifndef __H_INCLUDED__AWRTS_CUnitType
#define __H_INCLUDED__AWRTS_CUnitType

#include <Common/hrTypes.h>

namespace awrts
{

struct UnitType
{
	hrengin::u32 id;

	char * textUnitName;
	
	char * visualModelName;

	hrengin::u32 guiSelectionShapeId;

	hrengin::u32 statsHitPointsMax;
};

}

#endif//__H_INCLUDED__AWRTS_CUnitType