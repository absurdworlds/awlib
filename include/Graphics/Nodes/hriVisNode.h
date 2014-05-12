
#ifndef __HG_hriVisNode__
#define __HG_hriVisNode__

#include <Base/hrTypes.h>
#include <Base/Entities/hriBaseEntity.h>
#include <Graphics/Base/hriSceneNode.h>

namespace hrengin
{
namespace graphics
{
	

class hriVisNode : public hriSceneNode
{
	public:
		virtual void AttachToEntity(hriBaseEntity* attach) = 0;

		virtual i8 AddMesh(char * meshname) = 0;
		virtual void RemoveMesh(i8 meshslot) = 0;
		virtual void ReplaceMesh(i8 meshslot, char * meshname) = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hriVisNode__