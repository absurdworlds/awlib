#ifndef __H_INCLUDED__AWRTS_CUnitManager
#define __H_INCLUDED__AWRTS_CUnitManager

#include <vector>
#include <unordered_map>

#include <Common/hrTypes.h>

#include "CUnitType.h"
#include "CUnit.h"


namespace awrts
{

class CUnit;
class CUnitType;

class CUnitManager
{
public:
	CUnit& createUnit(hrengin::u32 id);
	void addType(CUnitType type);
private:
	std::vector<CUnit> mUnits;
	//std::vector<CUnitType> mUnitTypes;
	std::unordered_map<hrengin::u32,CUnitType> mUnitTypes;

};

}

#endif//__H_INCLUDED__AWRTS_CUnitManager