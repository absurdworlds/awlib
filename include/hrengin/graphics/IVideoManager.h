#ifndef _hrengin_IVideoManager_
#define _hrengin_IVideoManager_

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace graphics {
class IRenderingDevice;
class ISceneManager;
namespace gui {
class IGUIManager;
}

struct PlatformData {
	union {
		struct {
			void* wndHandle;
		} win32;
		struct {
		
		} linux;
	};
};

class IVideoManager {
public:
	virtual ~IVideoManager() {};

	virtual PlatformData getPlatformSpecificData() const = 0;

	virtual IRenderingDevice* getRenderingDevice() const = 0;
	virtual ISceneManager* getSceneManager() const = 0;
	virtual gui::IGUIManager* getGUIManager() const = 0;
	
	virtual bool step() = 0;
	virtual void wait() = 0;

	virtual bool isWindowActive() = 0;

	virtual u32 getTime() = 0;
};

HRENGINGRAPHICS_API IVideoManager* createVideoManager();

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_IVideoManager_
