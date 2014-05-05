
#ifndef __HR_I_UNIT_MANAGER__
#define __HR_I_UNIT_MANAGER__

#include "hriUnit.h"

namespace hrengin
{
	class hriUnitManager
	{
	public:
		virtual ~hriUnitManager() {};
		virtual hriUnit* CreateUnit(char* modelname) = 0;
	};
}

#endif __HR_I_UNIT_MANAGER__