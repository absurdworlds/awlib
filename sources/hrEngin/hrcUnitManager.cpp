
#include "hrcUnitManager.h"
#include "hrcUnit.h"
#include <hriModel.h>

namespace hrengin
{
hrcUnitManager::hrcUnitManager(hrcEncore* core)
	: EnCore(core)
{
	 
}

hriUnit* hrcUnitManager::CreateUnit(char* modelname) 
{
	hriUnit* newUnit = new hrcUnit(EnCore->GetGCore()->CreateModel("sotank.obj"));
	UnitList.push_back(newUnit);
	return newUnit;
} 

} //namespace hengin