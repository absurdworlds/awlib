
#include "CApplication.h"

namespace awrts
{

CApplication::CApplication()
{		
	videomgr = hrengin::graphics::GetManager();
		
	phymgr = hrengin::physics::GetManager ();
}

void CApplication::SetupTestScene()
{

}

}