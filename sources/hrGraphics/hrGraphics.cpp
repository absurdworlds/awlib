// hrGraphics.cpp : Defines the exported functions for the DLL application.
//

#include <hrGraphics.h>
#include "hrcGraphicsCore.h"
#include "hrgGlobal.h"

namespace hrengin
{
namespace graphics
{

HRGRAPHICS_API hriGraphicsCore* Startup(hriEncore* parent)
{
	hrcGraphicsCore* hWrapper = new hrcGraphicsCore(parent);

	return static_cast<hriGraphicsCore*>(hWrapper);
}

} // namespace graphics
}

#ifdef ___HRWINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
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