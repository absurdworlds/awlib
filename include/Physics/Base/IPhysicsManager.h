
#ifndef __H_INCLUDED__HRENGIN_IPhysicsManager
#define __H_INCLUDED__HRENGIN_IPhysicsManager

#include <Common/hrTypes.h>
#include <Base/Vector3d.h>

namespace hrengin
{
namespace physics
{

class ICollisionShape;
class IPhysicsObject;
class IPhysicsBody; //: IPhysicsObject;
class IPhysicsPhantom; //: IPhysicsObject;

class IPhysicsManager
{
	public:
		enum PHYS_BUILTIN_SHAPES
		{
			PHYS_SHAPE_SPHERE,
			PHYS_SHAPE_BOX,
			PHYS_SHAPE_CAPSULE,
			PHYS_SHAPE_CYLINDER,
			PHYS_SHAPE_CONE
		};

		virtual u32 MakeShape(PHYS_BUILTIN_SHAPES type, f32 x, f32 y, f32 z) = 0;
		virtual u32 AddShape(const char * modelname) = 0;

		virtual IPhysicsBody* CreateBody(const u32 shapeid) = 0;
		virtual IPhysicsPhantom* CreatePhantom(const u32 shapeid) = 0;

		virtual IPhysicsObject* CastRay(Vectorf3d from, Vectorf3d to) = 0;

		virtual bool Step() = 0;
};

}	
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IPhysicsManager