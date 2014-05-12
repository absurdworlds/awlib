
#ifndef __HG_hriPhysicsObject__
#define __HG_hriPhysicsObject__

#include <Base/hrVector3d.h>

namespace hrengin
{

class hriBaseEntity;

namespace physics
{

class hriCollisionShape;

class hriPhysicsObject
{
	public:
		virtual void AttachToEntity(hriBaseEntity* attach) = 0;

		virtual void SetPosition(Vectorf3d pos) = 0;
		virtual void SetRotation(Vectorf3d rot) = 0;
		//virtual void SetScale(Vectorf3d scale) = 0;
	protected:
};

}	
} // namespace hrengin

#endif//__HG_hriPhysicsObject__