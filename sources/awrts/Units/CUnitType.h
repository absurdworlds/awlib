#ifndef __H_INCLUDED__AWRTS_CUnitType
#define __H_INCLUDED__AWRTS_CUnitType

#include <Base/hrTypes.h>

namespace awrts
{

class CUnitType
{
public:
	hrengin::u32 mID;

	char * mTextUnitName;
	
	char * mVisualModelName;

	hrengin::u32 mStatsHitPointsMax;
};

}

#endif//__H_INCLUDED__AWRTS_CUnitType