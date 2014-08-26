#ifndef _hrengin_ISceneManager_
#define _hrengin_ISceneManager_

#include <hrengin/common/hrenginapi.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace graphics {
class ISceneNode;
class IVisNode;
class ICameraNode;
class ILightNode;

class ISceneManager {
public:
	/* Initialize a new scene, deleting an old scene */
	virtual void createScene() = 0;
	virtual void update() = 0;

	virtual ISceneNode* createSceneNode() = 0;
};

HRENGINGRAPHICS_API IVideoManager& getVideoManager();

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_ISceneManager_