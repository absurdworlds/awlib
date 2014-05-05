
#ifndef __HR_C_UNIT_MANAGER__
#define __HR_C_UNIT_MANAGER__

#include "hrcEncore.h"
#include <hriUnitManager.h>
#include <vector> // TODO: make custom implementation

namespace hrengin
{
	class hrcUnitManager : public hriUnitManager
	{
	public:
		hrcUnitManager(hrcEncore* core);
		virtual ~hrcUnitManager() {};
		virtual hriUnit* CreateUnit(char* modelname);
	private:
		std::vector<hriUnit*> UnitList;
		hrcEncore* EnCore;
	};
}

#endif __HR_C_UNIT_MANAGER__