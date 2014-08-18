
#ifndef __HG_CVideoManager_h__
#define __HG_CVideoManager_h__

#include <vector>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/gui/IGUIManager.h>
#include <hrengin/graphics/ISceneNode.h>
#include <hrengin/graphics/IVisNode.h>
#include <hrengin/graphics/ICameraNode.h>
#include <hrengin/graphics/ILightNode.h>

#include "CVisNode.h"
#include <Irrlicht/SAnimatedMesh.h>

namespace irr {
	class IrrlichtDevice;

	namespace video {
		class IVideoDriver;
	}

	namespace scene {
		class ISceneManager;
		class IAnimatedMesh;
		class ISceneCollisionManager;
	}

	namespace gui {
		class IGUIEnvironment;
	}
}

namespace hrengin {
	class CEncore;

namespace gui {
	class CGUIManager;
}

namespace graphics {

class CVisNode;

class CVideoManager : public IVideoManager
{
friend class CEncore;
friend class CGUIManager;
public:
	CVideoManager();
	virtual ~CVideoManager();
	virtual void CreateScene(); 
	virtual bool advance();
	virtual void draw();

	virtual PlatformData getPlatformSpecificData() const;

	virtual IVisNode* CreateVisObject();
	virtual ICameraNode* CreateCamera();
	virtual ILightNode* CreateLight();
	IVisNode* CVideoManager::createOildrum()
	{
		CVisNode* povisnode = new CVisNode();

		irr::scene::IMesh* mb = device->getSceneManager()->getGeometryCreator()->createCylinderMesh(0.572/2, 0.851, 16, irr::video::SColor(255,168,168,0));
		irr::scene::IAnimatedMesh* ma = new irr::scene::SAnimatedMesh(mb);

		irr::scene::IAnimatedMeshSceneNode* msh = device->getSceneManager()->addAnimatedMeshSceneNode(ma);
	
		povisnode->AddOildrum(msh);

		return povisnode;
	}

	virtual void AddNode(ISceneNode& node);

	virtual irr::scene::IAnimatedMesh* LoadMesh(const char * modelname);

	
	void drawLine(const Vector3d& from, const Vector3d& to, const Vector3d& color);

	
	void CVideoManager::ll1();
	void CVideoManager::end();

// irrlicht access
	virtual irr::IrrlichtDevice* GetDevice() const;
	virtual irr::video::IVideoDriver* GetDriver() const {return driver;};

	virtual irr::scene::ISceneManager* GetSceneMgr() const;
	virtual irr::scene::ISceneCollisionManager* getCollManager() const;
	virtual void drawVertexPrimitives(video::IVertexBuffer* vb) {};
	//virtual void drawIndexedVertexPrimitives(video::IVertexBuffer* vb, video::IIndexBuffer* ib);

private:
	std::vector<ISceneNode*> NodeList;
	std::vector<video::IRenderable*> extraRenderables_;

	irr::IrrlichtDevice*			device;
	irr::video::IVideoDriver*		driver;
	irr::gui::IGUIEnvironment*		guienv;
	irr::scene::ISceneManager*		scnmgr;
	irr::scene::ISceneCollisionManager*	colman;

	PlatformData platformdata_;

/*// DEBUG:
#ifdef _DEBUG
	bool __HRDEBUG_sceneCreated;
#endif*/

};

CVideoManager& getLocalManager();
	
} // namespace graphics
} // namespace hrengin

#endif//__HG_CVideoManager_h__