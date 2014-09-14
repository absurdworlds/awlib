#ifndef _hrengin_IVideoManager_
#define _hrengin_IVideoManager_

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace core{
class ISettingsManager;
}
namespace gui {
class IGUIManager;
}
namespace graphics {
class IRenderingDevice;
class ISceneManager;

class IVideoManager {
public:
	virtual ~IVideoManager() {};

	virtual IRenderingDevice* getRenderingDevice() const = 0;
	virtual ISceneManager* getSceneManager() const = 0;
	virtual gui::IGUIManager* getGUIManager() const = 0;
	
	virtual bool step() = 0;	// update()
	virtual void wait() = 0;

	virtual bool isWindowActive() = 0;

	virtual u32 getTime() = 0;
};

HRENGINGRAPHICS_API IVideoManager* createVideoManager(core::ISettingsManager* settings = 0);

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_IVideoManager_
