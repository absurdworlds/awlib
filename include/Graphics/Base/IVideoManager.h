#ifndef __H_INCLUDED__HRENGIN_IVideoManager
#define __H_INCLUDED__HRENGIN_IVideoManager

namespace hrengin
{
namespace graphics
{

class ISceneNode;
class IVisNode;
class ICameraNode;
class ILightNode;

class IVideoManager
{
	public:
		virtual void CreateScene() = 0;
		virtual bool Draw() = 0;

		virtual IVisNode* CreateVisObject() = 0;
		virtual ICameraNode* CreateCamera() = 0;
		virtual ILightNode* CreateLight() = 0;

		virtual void AddNode(ISceneNode& node) = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_IVideoManager_h__