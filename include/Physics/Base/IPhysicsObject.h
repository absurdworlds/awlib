#ifndef __H_INCLUDED__HRENGIN_IPhysicsObject
#define __H_INCLUDED__HRENGIN_IPhysicsObject

#include <Base/Vector3d.h>

namespace hrengin
{

class IBaseEntity;

namespace physics
{

class ICollisionShape;

class IPhysicsObject
{
	public:
		virtual void AttachToEntity(IBaseEntity* attach) = 0;

		virtual void SetPosition(Vectorf3d pos) = 0;
		virtual void SetRotation(Vectorf3d rot) = 0;
		//virtual void SetScale(Vectorf3d scale) = 0;
	protected:
};

}	
} // namespace hrengin

#endif//__HG_IPhysicsObject__