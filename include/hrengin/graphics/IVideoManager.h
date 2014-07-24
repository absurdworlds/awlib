#ifndef __H_INCLUDED__HRENGIN_IVideoManager
#define __H_INCLUDED__HRENGIN_IVideoManager

#include <hrengin/common/hrenginapi.h>
#include <hrengin/common/Vector3d.h>

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
	virtual bool advance() = 0;
	// draw the scene
	virtual void draw() = 0;

	virtual PlatformData getPlatformSpecificData() const = 0;

	virtual IVisNode* CreateVisObject() = 0;
	virtual ICameraNode* CreateCamera() = 0;
	virtual ILightNode* CreateLight() = 0;
	virtual IVisNode* createOildrum() = 0;

	virtual void AddNode(ISceneNode& node) = 0;
	virtual void drawLine(const Vector3d& from, const Vector3d& to, const Vector3d& color) = 0;
	
	virtual void ll1()=0;
	virtual void end()=0;
};

HRENGINGRAPHICS_API IVideoManager& getVideoManager();

} // namespace graphics
} // namespace hrengin

#endif//__HG_IVideoManager_h__