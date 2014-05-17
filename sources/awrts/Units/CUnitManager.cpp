
#include "CUnit.h"
#include "CUnitType.h"
#include "CUnitManager.h"
#include "../CApplication.h"

namespace awrts
{

CUnit& CUnitManager::createUnit(hrengin::u32 id)
{
	CUnitType unit_type = mUnitTypes[id];
	CUnit unit(unit_type);
	CApplication& app = CApplication::getInstance();

	unit.mVisual = app.videomgr->CreateVisObject();
	unit.mVisual->AddMesh(unit_type.mVisualModelName);

	mUnits.push_back(unit);
	return mUnits.back();
};

void CUnitManager::addType(CUnitType type)
{
	if(mUnitTypes.find(type.mID) == mUnitTypes.end())
	{
		mUnitTypes[type.mID] = type;
	}
}

}
