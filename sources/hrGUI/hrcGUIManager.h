
#ifndef __HR_C_GUI_MANAGER_H__
#define __HR_C_GUI_MANAGER_H__

#include <hriEncore.h>
#include <hriGraphicsCore.h> // since both Graphics and GUI depend on Irrlicht engine, GUI lays all the rendering routines on hrGraphics 
#include <hriGUIManager.h>
#include <irrlicht.h>

namespace hrengin
{
namespace gui
{

	class hrcGUIManager : public hriGUIManager
	{
		public:
			hrcGUIManager(hriEncore* p);
			virtual ~hrcGUIManager() {}
		private:			
			hriEncore*		parent;

			irr::gui::IGUIEnvironment*	guienv;
	};

} // namespace gui
} // namespace hrengin

#endif //__HR_C_GUI_MANAGER_H__