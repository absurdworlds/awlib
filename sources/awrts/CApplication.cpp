
#include "Units/CUnitManager.h"
#include "CMapManager.h"

#include "CApplication.h"


namespace awrts
{

CApplication::CApplication()
: videomgr (hrengin::graphics::getVideoManager()),
  phymgr (hrengin::physics::getPhysicsManager()),
  entmgr (hrengin::getEntityManager()),
  eventmgr (hrengin::getEventManager()) 
{
	videomgr.CreateLight();



	//unitmgr = new CUnitManager();
	//mapmgr = new CMapManager();

	//encore = hrengin::KickstartEngine();
}

void CApplication::SetupTestScene()
{

}

}