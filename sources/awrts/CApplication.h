#ifndef __H_INCLUDED_AWRTS_CApplication
#define __H_INCLUDED_AWRTS_CApplication

#include <hrengin/base/IEncore.h>
#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/physics/IPhysicsManager.h>
#include <hrengin/sound/ISoundManager.h>
#include <hrengin/entities/IEntityManager.h>
#include <hrengin/entities/IEventManager.h>

#include "Units/CUnitManager.h"
#include "CMapManager.h"

namespace awrts {

class CApplication
{
public:
	static CApplication& getInstance()
	{
		static CApplication instance;
		return instance;
	}

	void SetupTestScene();
	
	//hrengin::IEncore& encore;
	hrengin::physics::IPhysicsManager& phymgr;
	hrengin::graphics::IVideoManager& videomgr;
	hrengin::IEntityManager& entmgr;
	hrengin::IEventManager& eventmgr;
	awrts::CUnitManager unitmgr;
	awrts::CMapManager mapmgr;
	bool profiling = 0;

private:
	CApplication();
};


}

#endif//__H_INCLUDED_AWRTS_CApplication