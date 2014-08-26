#ifndef _hrengin_CSceneManager_
#define _hrengin_CSceneManager_

#include <hrengin/common/hrenginapi.h>
#include <hrengin/common/Vector3d.h>

#include <hrengin/graphics/ISceneManager.h>

namespace hrengin {
namespace graphics {

class CSceneManager : public ISceneManager {
public:
	/* Initialize a new scene, deleting an old scene */
	virtual void createScene() = 0;
	virtual void update() = 0;

	virtual ISceneNode* createSceneNode() = 0;
};

//HRENGINGRAPHICS_API IVideoManager& getVideoManager();

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CSceneManager_