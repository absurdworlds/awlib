
#ifndef __HG_hrcVideoManager_h__
#define __HG_hrcVideoManager_h__

#include <Graphics/Base/hriVideoManager.h>
#include <GUI/Base/hriGUIManager.h>
#include <Graphics/Base/hriSceneNode.h>
#include <Graphics/Nodes/hriVisNode.h>
#include <Graphics/Nodes/hriCameraNode.h>
#include <Graphics/Nodes/hriLightNode.h>

#include <vector>

namespace irr
{
	class IrrlichtDevice;

	namespace video
	{
		class IVideoDriver;
	}

	namespace scene
	{
		class ISceneManager;
	}

	namespace gui
	{
		class IGUIEnvironment;
	}
}

namespace hrengin
{
namespace graphics
{

class hrcVideoManager : public hriVideoManager
{
	friend class hrcGUIManager;
	public:
		hrcVideoManager();
		virtual ~hrcVideoManager();
		virtual void CreateScene();
		virtual bool Draw();
		
		virtual hriVisNode* CreateModel(const char* modelname);
		virtual hriCameraNode* CreateCamera();
		virtual hriLightNode* CreateLight();

		virtual void AddNode(hriSceneNode& node);

	private:
		std::vector<hriSceneNode*> NodeList;

		irr::IrrlichtDevice*		device;
		irr::video::IVideoDriver*	driver;
		irr::scene::ISceneManager*	scnmgr;
		irr::gui::IGUIEnvironment*	guienv;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hrcVideoManager_h__