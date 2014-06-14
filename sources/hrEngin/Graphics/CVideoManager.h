
#ifndef __HG_CVideoManager_h__
#define __HG_CVideoManager_h__

#include <vector>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/gui/IGUIManager.h>
#include <hrengin/graphics/ISceneNode.h>
#include <hrengin/graphics/IVisNode.h>
#include <hrengin/graphics/ICameraNode.h>
#include <hrengin/graphics/ILightNode.h>

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

	class CEncore;

namespace gui
{
	class CGUIManager;
}

namespace graphics
{

class CVisNode;

class CVideoManager : public IVideoManager
{
	friend class CEncore;
	friend class CGUIManager;
	public:
		CVideoManager();
		virtual ~CVideoManager();
		virtual void CreateScene();
		virtual bool Draw();
		
		virtual IVisNode* CreateVisObject();
		virtual ICameraNode* CreateCamera();
		virtual ILightNode* CreateLight();

		virtual void AddNode(ISceneNode& node);
		
		virtual irr::scene::IAnimatedMesh* LoadMesh(const char * modelname);

	// irrlicht access
		virtual irr::IrrlichtDevice* GetDevice() const;

		virtual irr::scene::ISceneManager* GetSceneMgr() const;
		virtual irr::scene::ISceneCollisionManager* getCollManager() const;

	private:
		std::vector<ISceneNode*> NodeList;

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

#endif//__HG_CVideoManager_h__