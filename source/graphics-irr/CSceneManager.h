#ifndef _hrengin_CSceneManager_
#define _hrengin_CSceneManager_

#include <vector>

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

#include <hrengin/graphics/ISceneManager.h>

namespace irr {
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
	CSceneManager(irr::scene::ISceneManager* irrSceneManager);

	virtual void createScene();

	virtual void drawScene();

	virtual void update();
	
	virtual IVisNode* createMeshSceneNode();
	virtual ICameraNode* createCameraSceneNode();
	virtual ILightNode* createLightSceneNode();
private:
	std::vector<ISceneNode*> NodeList;

	irr::scene::ISceneManager*		scnmgr;
	irr::scene::ISceneCollisionManager*	colman;
};

ISceneManager* createSceneManager();

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CSceneManager_
