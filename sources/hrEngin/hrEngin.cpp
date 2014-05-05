// This is a part of hrEngin
// See copyright notice in hrEngin.h, for conditions of distribution and use.

// THIS FILE: 

#include <hrConfig.h>

#ifdef ___HRWINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "hrEngin.h"
#include "hrcEncore.h"

namespace hrengin
{


HRENGIN_API hriEncore* KickstartEngine ()
{
	return new hrcEncore();
}

} // namespace hrengin


#ifdef ___HRWINDOWS
#pragma comment(lib, "hrGraphics.lib")
#pragma comment(lib, "hrGUI.lib")

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