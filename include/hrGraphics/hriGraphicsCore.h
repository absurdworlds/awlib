
#ifndef __HR_I_GRAPHICS_CORE_H__
#define __HR_I_GRAPHICS_CORE_H__

#include "hriModel.h"

namespace irr
{
namespace scene
{
	class ISceneManager;
}
}

namespace hrengin
{
namespace graphics
{

	class hriGraphicsCore
	{
		public:
			virtual ~hriGraphicsCore() {}
			// virtual void Startup() = 0; -- external function used
			virtual void CreateScene() = 0;
			virtual bool Draw() = 0;

			virtual hriModel* CreateModel(const char* modelname) = 0;

			virtual irr::scene::ISceneManager* GetSceneManager() = 0;
	};

} // namespace graphics
} // namespace hrengin

#endif //__HR_I_GRAPHICS_CORE_H__