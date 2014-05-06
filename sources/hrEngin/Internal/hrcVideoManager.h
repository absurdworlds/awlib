
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
		class IAnimatedMesh;
	}

	namespace gui
	{
		class IGUIEnvironment;
	}
}

namespace hrengin
{

namespace gui
{
	class hrcGUIManager;
}

namespace graphics
{

class hrcVisNode;

class hrcVideoManager : public hriVideoManager
{
	friend class hrcGUIManager;
	public:
		hrcVideoManager();
		virtual ~hrcVideoManager();
		virtual void CreateScene();
		virtual bool Draw();
		
		virtual hriVisNode* CreateVisObject();
		virtual hriCameraNode* CreateCamera();
		virtual hriLightNode* CreateLight();

		virtual void AddNode(hriSceneNode& node);
		
	//protected:
		virtual irr::scene::ISceneManager* GetSceneMgr() const;
		virtual irr::scene::IAnimatedMesh* LoadMesh(const char * modelname);

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