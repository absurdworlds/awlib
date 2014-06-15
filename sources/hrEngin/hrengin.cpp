
#include <hrengin/hrengin.h>

#include "Common/CInternalsManager.h"
#include "Common/hrFilesystem.h"
#include "Common/CEncore.h"
#include "Entities/CEventManager.h"

#ifdef _HR_PHYSICS_HAVOK
#include "Base/Config/HavokMagicSpells.h"
#elif defined(_HR_PHYSICS_NEWTON)
#endif

namespace hrengin
{

HRENGIN_API IEncore* KickstartEngine ()
{
	return new CEncore();
}

HRENGIN_API IEntityManager* GetManager ()
{
	if(!__HRIM.entmgr)
	{
		__HRIM.entmgr = new CEntityManager();
	}
	return __HRIM.entmgr;
}


HRENGIN_API IEventManager* GetEventManager ()
{
	return new CEventManager();
}

namespace graphics
{
HRENGIN_API IVideoManager* GetManager ()
{
	if(!__HRIM.videomgr)
	{
		__HRIM.videomgr = new CVideoManager;
	}
	return __HRIM.videomgr;
}

}

namespace physics
{
HRENGIN_API IPhysicsManager* GetManager ()
{
	if(!__HRIM.physmgr)
	{
		/*#ifdef _HR_PHYSICS_HAVOK
		__HRIM.physmgr = new CHavokPhysics();
		#elif defined(_HR_PHYSICS_NEWTON)
		__HRIM.physmgr = new CNewtonPhysics();
		#endif*/
		__HRIM.physmgr = new CBulletPhysics();
		/*u32 shape = __HRIM.physmgr->MakeShape(IPhysicsManager::PHYS_SHAPE_SPHERE,5.);
		IPhysicsPhantom* Phantom = __HRIM.physmgr->CreatePhantom(shape);
		fprintf(stderr, "Object is: %d\n", Phantom);*/
	}

	return __HRIM.physmgr;
}

} 

namespace gui
{
HRENGIN_API IGUIManager* GetManager ()
{
	return 0;
}

HRENGIN_API IInputManager* GetInputManager ()
{
	if(!__HRIM.inputmgr)
	{
		__HRIM.inputmgr = new CInputManager();
	}

	return __HRIM.inputmgr;
}

} //end namespace gui

}

#ifdef _HR_�INDOWS

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