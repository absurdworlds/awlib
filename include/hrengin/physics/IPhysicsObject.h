#ifndef __H_INCLUDED__HRENGIN_IPhysicsObject
#define __H_INCLUDED__HRENGIN_IPhysicsObject

#include <hrengin/common/Vector3d.h>
		  
namespace hrengin
{

class IBaseEntity;

namespace physics
{

class ICollisionShape;

class IPhysicsObject
{
	public:
		virtual void attachToEntity(IBaseEntity* attach) = 0;
		virtual IBaseEntity* getEntity() = 0;

		virtual void setPosition(Vector3d pos) = 0;
		virtual void setRotation(Vector3d rot) = 0;
		//virtual void SetScale(Vectorf3d scale) = 0;
	protected:
};

}	
} // namespace hrengin

#endif//__HG_IPhysicsObject__