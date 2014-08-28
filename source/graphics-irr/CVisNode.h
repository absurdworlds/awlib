
#ifndef __HG_CVisNode__
#define __HG_CVisNode__

#include <array>

#include <Irrlicht/Irrlicht.h>

#include <hrengin/common/types.h>

#include <hrengin/graphics/IVisNode.h>

namespace hrengin
{
class IBaseEntity;

namespace graphics
{
	
class CVisNode : public IVisNode
{
	public:
		CVisNode();
		CVisNode(IBaseEntity* attach);
		
		virtual void AttachToEntity(IBaseEntity* attach);

		virtual void setPosition(Vector3d pos);
		virtual void setRotation(Vector3d rot);
		//virtual void SetScale(Vectorf3d scale);

		virtual i8 AddMesh(char * meshname);
		virtual i8 AddOildrum(irr::scene::IAnimatedMeshSceneNode* mesh)
		{
			if(lastFreeSlot < maxFreeSlot) {
				meshSlots[lastFreeSlot] = mesh;
				meshSlots[lastFreeSlot]->setAutomaticCulling(irr::scene::EAC_FRUSTUM_BOX);
				++lastFreeSlot;
				return lastFreeSlot-1;
			} else {
				return -1;
			}
		}
		virtual void RemoveMesh(i8 meshslot);
		virtual void ReplaceMesh(i8 meshslot, char * meshname);

	private:
		IBaseEntity* attachedTo;

		i8 lastFreeSlot;
		static const i8 maxFreeSlot = 16;

		std::array<irr::scene::IAnimatedMeshSceneNode*, maxFreeSlot> meshSlots;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_CVisNode__