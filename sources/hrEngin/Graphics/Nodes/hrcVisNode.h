
#ifndef __HG_hrcVisNode__
#define __HG_hrcVisNode__

#include <Base/hrTypes.h>
#include <Base/Entities/hriBaseEntity.h>
#include <Graphics/Nodes/hriVisNode.h>
#include <Graphics/Base/hriVideoManager.h>

#include <Irrlicht.h>

#include <array>

namespace hrengin
{
namespace graphics
{
	
class hrcVisNode : public hriVisNode
{
	public:
		hrcVisNode(hriVideoManager* Vmgr);
		hrcVisNode(hriVideoManager* Vmgr, hriBaseEntity* attach);
		
		virtual void AttachToEntity(hriBaseEntity* attach);

		virtual void SetPosition(Vectorf3d pos);
		virtual void SetRotation(Vectorf3d rot);
		virtual void SetScale(Vectorf3d scale);

		virtual i8 AddMesh(char * meshname);
		virtual void RemoveMesh(i8 meshslot);
		virtual void ReplaceMesh(i8 meshslot, char * meshname);

	private:
		hriVideoManager* videomgr;
		hriBaseEntity* attachedTo;

		i8 lastFreeSlot;
		static const i8 maxFreeSlot = 16;

		std::array<irr::scene::IAnimatedMeshSceneNode*, maxFreeSlot> meshSlots;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hrcVisNode__