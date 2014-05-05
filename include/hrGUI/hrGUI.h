
#ifndef __HR_GUI_H__
#define __HR_GUI_H__

#include <hrConfig.h>

#ifdef HRGUI_EXPORTS
#define HRGUI_API __declspec(dllexport)
#else
#define HRGUI_API __declspec(dllimport)
#endif

#include <hriEncore.h>
#include <hriGUIManager.h>

namespace hrengin
{
namespace gui
{
	HRGUI_API hriGUIManager* Startup(hriEncore* parent);

} // namespace gui
} // namespace hrengin

#endif//__HR_GUI_H__