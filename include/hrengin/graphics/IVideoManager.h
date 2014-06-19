#ifndef __H_INCLUDED__HRENGIN_IVideoManager
#define __H_INCLUDED__HRENGIN_IVideoManager

#include <hrengin/common/hrenginapi.h>

namespace hrengin {
namespace graphics {

class ISceneNode;
class IVisNode;
class ICameraNode;
class ILightNode;

struct PlatformData
{
	union
	{
		struct
		{
			void* wndHandle;
		} win32;
	};
};

class IVideoManager
{
public:
	virtual void CreateScene() = 0;
	virtual bool Draw() = 0;

	virtual PlatformData getPlatformSpecificData() const = 0;

	virtual IVisNode* CreateVisObject() = 0;
	virtual ICameraNode* CreateCamera() = 0;
	virtual ILightNode* CreateLight() = 0;

	virtual void AddNode(ISceneNode& node) = 0;
};

HRENGINGRAPHICS_API IVideoManager& getVideoManager();

} // namespace graphics
} // namespace hrengin

#endif//__HG_IVideoManager_h__