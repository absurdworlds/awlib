#ifndef __H_INCLUDED_AWRTS_CApplication
#define __H_INCLUDED_AWRTS_CApplication


#include <hrEngin.h>



namespace awrts
{

class CUnitManager;
class CMapManager;

class CApplication
{
public:
	static CApplication& getInstance()
	{
		static CApplication instance;
		return instance;
	}

	void SetupTestScene();
	
	hrengin::IEncore* encore;
	hrengin::physics::IPhysicsManager* phymgr;
	hrengin::graphics::IVideoManager* videomgr;
	hrengin::IEntityManager* entmgr;
	hrengin::IEventManager* eventmgr;
	awrts::CUnitManager* unitmgr;
	awrts::CMapManager* mapmgr;

private:	
	CApplication();
};


}

#endif//__H_INCLUDED_AWRTS_CApplication