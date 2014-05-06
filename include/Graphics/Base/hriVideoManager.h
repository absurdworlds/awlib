
#ifndef __HG_hriVideoManager_h__
#define __HG_hriVideoManager_h__

namespace irr
{
	namespace scene
	{
		class ISceneManager;
		class IAnimatedMesh;
	}
}

namespace hrengin
{
namespace graphics
{

class hriSceneNode;
class hriVisNode;
class hriCameraNode;
class hriLightNode;

class hriVideoManager
{
	public:
		virtual void CreateScene() = 0;
		virtual bool Draw() = 0;

		virtual hriVisNode* CreateVisObject() = 0;
		virtual hriCameraNode* CreateCamera() = 0;
		virtual hriLightNode* CreateLight() = 0;

		virtual void AddNode(hriSceneNode& node) = 0;

		//virtual IAnimatedMeshSceneNode* LoadModel(const char* modelname) = 0;

	//protected:
		virtual irr::scene::ISceneManager* GetSceneMgr() const = 0;
		virtual irr::scene::IAnimatedMesh* LoadMesh(const char * modelname) = 0;

};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hriVideoManager_h__