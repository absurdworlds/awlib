
#ifndef __HG_hriPhysicsManager__
#define __HG_hriPhysicsManager__

#include <Base/hrTypes.h>
#include <Base/hrVector3d.h>

namespace hrengin
{
namespace physics
{

class hriCollisionShape;
class hriPhysicsObject;
class hriPhysicsBody; //: hriPhysicsObject;
class hriPhysicsPhantom; //: hriPhysicsObject;

class hriPhysicsManager
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

		virtual hriPhysicsBody* CreateBody(const u32 shapeid) = 0;
		virtual hriPhysicsPhantom* CreatePhantom(const u32 shapeid) = 0;

		virtual hriPhysicsObject* CastRay(Vectorf3d from, Vectorf3d to) = 0;

		virtual bool Step() = 0;
};

}	
} // namespace hrengin

#endif//__HG_hriPhysicsManager__