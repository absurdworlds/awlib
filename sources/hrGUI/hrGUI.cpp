// hrGUI.cpp : Defines the exported functions for the DLL application.
//

#include <hrGUI.h>
#include "hrcGUIManager.h"
#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

namespace hrengin
{
namespace gui
{
	HRGUI_API hriGUIManager* Startup(hriEncore* parent)
	{
		return new hrcGUIManager(parent);
	}

} // namespace gui
} // namespace hrengin


#ifdef ___HRWINDOWS

#pragma comment(lib, "hrGraphics.lib")

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