
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
		class ISceneCollisionManager;
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
		
		virtual irr::scene::IAnimatedMesh* LoadMesh(const char * modelname);

	// irrlicht access
		virtual irr::IrrlichtDevice* GetDevice() const;

		virtual irr::scene::ISceneManager* GetSceneMgr() const;
		virtual irr::scene::ISceneCollisionManager* getCollManager() const {return 0;}

	private:
		std::vector<hriSceneNode*> NodeList;

		irr::IrrlichtDevice*				device;
		irr::video::IVideoDriver*			driver;
		irr::gui::IGUIEnvironment*			guienv;
		irr::scene::ISceneManager*			scnmgr;
		irr::scene::ISceneCollisionManager* colman;

	/*// DEBUG:
	#ifdef _DEBUG
		bool __HRDEBUG_sceneCreated;
	#endif*/

};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hrcVideoManager_h__