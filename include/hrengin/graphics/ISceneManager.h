#ifndef _hrengin_ISceneManager_
#define _hrengin_ISceneManager_

#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace graphics {
class ISceneNode;
class IVisNode;
class ICameraNode;
class ILightNode;

class ISceneManager {
public:
	virtual ~ISceneManager() {};

	virtual bool step() = 0;

	/* Initialize a new scene, clearing the current scene */
	virtual void createScene() = 0;
	virtual void drawScene() = 0;
	virtual void update() = 0;

	virtual IVisNode* createMeshSceneNode() = 0;
	virtual ICameraNode* createCameraSceneNode() = 0;
	virtual ILightNode* createLightSceneNode() = 0;
};


} // namespace graphics
} // namespace hrengin

#endif//_hrengin_ISceneManager_