/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISceneNode_
#define _hrengin_ISceneNode_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Matrix4.h>
#include <hrengin/common/Quaternion.h>

namespace hrengin {

class IBaseEntity;

namespace graphics {

//! A node in the scene graph
class ISceneNode {
public:
	virtual void setParentEntity(IBaseEntity* parent) = 0;

	virtual void setPosition(Vector3d<f32> pos) = 0;
	virtual void setRotation(Vector3d<f32> euler) = 0;

	virtual void setOrientation(Quaternion<f32> const& quat) {};

	// not supported
	//virtual void setScale(Vector3d<f32> scale) = 0;
};

} // namespace graphics
} // namespace hrengin

#endif //_hrengin_ISceneNode_
