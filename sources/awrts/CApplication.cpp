
#include "Units/CUnitManager.h"
#include "CMapManager.h"

#include "CApplication.h"


namespace awrts
{

CApplication::CApplication()
{
	videomgr = hrengin::graphics::GetManager();
	videomgr->CreateLight();

	phymgr = hrengin::physics::GetManager ();
	entmgr = hrengin::GetManager();

	unitmgr = new CUnitManager();
	mapmgr = new CMapManager();
}

void CApplication::SetupTestScene()
{

}

}