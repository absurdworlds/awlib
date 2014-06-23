#ifndef __HRENGIN_PHYSICS_PhysModel_H__
#define __HRENGIN_PHYSICS_PhysModel_H__

#include <hrengin/common/hrTypes.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace physics {
enum PhysShape
{
	PHYS_SHAPE_SPHERE,
	PHYS_SHAPE_BOX,
	PHYS_SHAPE_CAPSULE,
	PHYS_SHAPE_CYLINDER,
	PHYS_SHAPE_CONE
};

struct PhysModel {
	union {
		struct Procedural {
			PhysShape shape;
			f64 xl, xh, yl, yh, zl, zh;
		};
		struct Mesh {
			f32* verts;
		};
	};
	bool isProcedural;
};

} // namespace physics
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_PhysModel_H__