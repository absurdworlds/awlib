
#ifndef __HR_C_MODEL__
#define __HR_C_MODEL__

#include <hriModel.h>
#include <hriGraphicsCore.h>
#include "Irr.h"


namespace hrengin
{
namespace graphics
{

class hrcModel : public hriModel
{
	public:
		// default model
		// (a cuboid with dimentsions 1.8x0.6x0.4m)
		hrcModel(hriGraphicsCore* gcore);
		// load model with following name
		hrcModel(hriGraphicsCore* gcore, irr::io::path modelname);

		virtual ~hrcModel();
	private:		
		hriGraphicsCore* GCore;

		irr::scene::IAnimatedMesh* mesh;
		irr::scene::IAnimatedMeshSceneNode* node;
		//temporary
};
}
} // namespace hrengin

#endif // __HR_C_MODEL__