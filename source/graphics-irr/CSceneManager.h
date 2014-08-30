#ifndef _hrengin_CSceneManager_
#define _hrengin_CSceneManager_

#include <vector>

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

#include <hrengin/graphics/ISceneManager.h>
#include <hrengin/graphics/IRenderingDevice.h>
#include <hrengin/graphics/ISceneNode.h>
#include <hrengin/graphics/IVisNode.h>
#include <hrengin/graphics/ICameraNode.h>
#include <hrengin/graphics/ILightNode.h>

namespace irr {
class IrrlichtDevice;
namespace scene {
class ISceneManager;
class IAnimatedMesh;
class ISceneCollisionManager;
}
}

namespace hrengin {
namespace graphics {

class CSceneManager : public ISceneManager {
public:
	CSceneManager(irr::scene::ISceneManager* irrSceneManager, IRenderingDevice* renderer, irr::IrrlichtDevice* device);

	virtual void createScene();

	virtual void drawScene();

	virtual void update();
	
	virtual IVisNode* createMeshSceneNode(const char* meshname);
	//virtual IVisNode* createMeshSceneNode(IMesh* mesh);
	virtual ICameraNode* createCameraSceneNode();
	virtual ILightNode* createLightSceneNode();
private:
	std::vector<ISceneNode*> NodeList;
	
	irr::IrrlichtDevice* device_;
	irr::scene::ISceneManager*		scnmgr;
	irr::scene::ISceneCollisionManager*	colman;
public:
	irr::scene::IAnimatedMesh* convertMesh(const char* meshname);
	//irr::scene::IAnimatedMesh* convertMesh(IMesh* mesh);
};

ISceneManager* createSceneManager();

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CSceneManager_
