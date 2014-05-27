#ifndef __H_INCLUDED__AWRTS_CUnitManager
#define __H_INCLUDED__AWRTS_CUnitManager

#include <vector>
#include <unordered_map>

#include <Common/hrTypes.h>

#include "UnitType.h"
#include "CUnit.h"


namespace awrts
{

class CUnit;
class CUnitType;

class CUnitManager
{
	public:
		CUnit& createUnit(hrengin::u32 id, hrengin::Vector3d position, hrengin::f32 facing=0.0f);
		void addType(UnitType type);
		std::unordered_map<hrengin::u32,UnitType> unitTypes_;
	private:
		std::vector<CUnit*> units_;
		//std::vector<CUnitType> mUnitTypes;
};

}

#endif//__H_INCLUDED__AWRTS_CUnitManager