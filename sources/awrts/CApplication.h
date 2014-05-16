#ifndef __H_INCLUDED_AWRTS_CApplication
#define __H_INCLUDED_AWRTS_CApplication


#include <hrEngin.h>


namespace awrts
{

class CApplication
{
public:
	static CApplication& getInstance()
	{
		static CApplication instance;
		return instance;
	}

	void SetupTestScene();

	hrengin::graphics::IVideoManager* videomgr;
	hrengin::physics::IPhysicsManager* phymgr;
	hrengin::IEntityManager* entmgr;

private:	
	CApplication();
};


}

#endif//__H_INCLUDED_AWRTS_CApplication