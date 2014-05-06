
#include <hrEngin.h>
#include "hrcEncore.h"

#ifdef _HR_PHYSICS_HAVOK
#include <Common/Base/hkBase.h>
#include "Base/Config/HavokMagicSpells.h"
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
	return new hrcVideoManager;
}

}

namespace physics
{
HRENGIN_API hriPhysicsManager* GetManager ()
{
	return 0;
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