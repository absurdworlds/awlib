#ifndef __H_INCLUDED_AWRTS_awrts
#define __H_INCLUDED_AWRTS_awrts

#include <hrEngin.h>

namespace awrts
{

class CApplication
{
public:
	
	CApplication();
	void SetupTestScene();

	hrengin::graphics::IVideoManager* videomgr;
	hrengin::physics::IPhysicsManager* phymgr;
	hrengin::IEntityManager* entmgr;

};

CApplication::CApplication()
{		
	videomgr = hrengin::graphics::GetManager();
		
	phymgr = hrengin::physics::GetManager ();
}

void CApplication::SetupTestScene()
{

}

}

#endif