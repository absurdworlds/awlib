#ifndef __HRENGIN_hrenginmodels_H__
#define __HRENGIN_hrenginmodels_H__

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
enum Shape
{
	SHAPE_SPHERE,
	SHAPE_BOX,
	SHAPE_CAPSULE,
	SHAPE_CYLINDER,
	SHAPE_CONE
};

struct ShapeModel {
	Shape shape;
	f32 x, y, z;
	f32 w, h, l;
};

struct MeshModel {
	f32* verts;
};

} // namespace hrengin

#endif __HRENGIN_hrenginmodels_H__