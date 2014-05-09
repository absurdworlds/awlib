
#include <hrEngin.h>
#include "Internal/hrcInternalsManager.h"
#include "Internal/hrFilesystem.h"
#include "hrcEncore.h"

#ifdef _HR_PHYSICS_HAVOK
#include "Base/Config/HavokMagicSpells.h"
#elif defined(_HR_PHYSICS_NEWTON)
#endif

namespace hrengin
{

HRENGIN_API hriEncore* KickstartEngine ()
{
	return new hrcEncore();
}

HRENGIN_API hriEntityManager* GetManager ()
{
	return 0;
}


namespace graphics
{
HRENGIN_API hriVideoManager* GetManager ()
{
	if(!__HRIM.videomgr)
	{
		__HRIM.videomgr = new hrcVideoManager;
	}
	return __HRIM.videomgr;
}

}

namespace physics
{
HRENGIN_API hriPhysicsManager* GetManager ()
{
	if(!__HRIM.physmgr)
	{
		#ifdef _HR_PHYSICS_HAVOK
		__HRIM.physmgr = new hrcHavokPhysics();
		#elif defined(_HR_PHYSICS_NEWTON)
		__HRIM.physmgr = new hrcNewtonPhysics();
		#endif
	}

	return __HRIM.physmgr;
}

} 

namespace gui
{
HRENGIN_API hriGUIManager* Startup()
{
	return 0;
}

} 

}

#ifdef _HR_ØINDOWS

#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif