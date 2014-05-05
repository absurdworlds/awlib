
#ifndef __HR_C_GRAPHICS_CORE_H__
#define __HR_C_GRAPHICS_CORE_H__

#include <hriEnCore.h>
#include <hriGraphicsCore.h>
#include "Irr.h"

namespace hrengin
{
namespace graphics
{

	class hrcGraphicsCore : public hriGraphicsCore
	{
		public: //public public
			hrcGraphicsCore(hriEncore* p);
			virtual ~hrcGraphicsCore();

			virtual void CreateScene();
			virtual bool Draw();

			virtual hriModel* CreateModel(const char* modelname);
		public:
			irr::scene::ISceneManager* GetSceneManager();

		private:
			hriEncore*		parent;
			// changed visibility to private
			// to make it easier for export
			irr::IrrlichtDevice*		device;
			irr::video::IVideoDriver*	driver;
			irr::scene::ISceneManager*	scnmgr;
			irr::gui::IGUIEnvironment*	guienv; // -- now property of hrcGUIManager
	};

} // namespace graphics
} // namespace hrengin

#endif __HR_C_GRAPHICS_CORE_H__