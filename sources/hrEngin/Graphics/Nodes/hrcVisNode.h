
#ifndef __HG_hrcVisNode__
#define __HG_hrcVisNode__

#include <Base/Entities/hriBaseEntity.h>
#include <Graphics/Nodes/hriVisNode.h>
#include <Irrlicht.h>

namespace hrengin
{
namespace graphics
{
	

class hrcVisNode : public hriVisNode
{
	public:
		hrcVisNode();
		hrcVisNode(hriBaseEntity* attach);
		
		virtual void AttachToEntity(hriBaseEntity* attach);

		virtual u8 AddMesh(char * meshname);
		virtual void RemoveMesh(u8 meshslot);
		virtual void ReplaceMesh(u8 meshslot, char * meshname);
	private:
		hriBaseEntity* AttachedTo;
		irr::scene::IAnimatedMeshSceneNode* ModelSlots[16];
};

	
} // namespace graphics
} // namespace hrengin

#endif