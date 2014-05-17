#ifndef __H_INCLUDED__HRENGIN_IVisNode
#define __H_INCLUDED__HRENGIN_IVisNode

#include <Common/hrTypes.h>
#include <Base/Entities/IBaseEntity.h>
#include <Graphics/Base/ISceneNode.h>

namespace hrengin
{
namespace graphics
{
	

class IVisNode : public ISceneNode
{
	public:
		virtual void AttachToEntity(IBaseEntity* attach) = 0;

		virtual i8 AddMesh(char * meshname) = 0;
		virtual void RemoveMesh(i8 meshslot) = 0;
		virtual void ReplaceMesh(i8 meshslot, char * meshname) = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IVisNode