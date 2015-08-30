/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_BaseEntity_
#define _awrts_BaseEntity_

#include <vector>
#include <algorithm>

#include <awrts/common/types.h>
#include <awrts/math/Vector3d.h>

#include <awrts/scene/EntityNode.h>
//#include "Base/VirtualObject.h"

namespace awrts {
namespace scene {
class EntityNode;
}

namespace game {
enum EntFlag : u32 {
};

//! Base for game entities
class Entity {
	friend class scene::EntityNode;
public:
	virtual ~Entity()
	{
	}

	//! get the entity type identifier
	virtual u32 getEntityIdentifier()
	{
		return 0;
	}

	virtual bool getEntityFlag(EntFlag flag)
	{
		return (entflags_ & flag) != 0;
	}

	// sync all attached nodes and entities
	virtual void sync() = 0;

	// set entity's position
	virtual void setPosition(Vector3d<f32> position) = 0;
	// set entity's rotation
	virtual void setRotation(Vector3d<f32> rotation) = 0;

	virtual Vector3d<f32> getPosition() const = 0;
	virtual Vector3d<f32> getRotation() const = 0;

protected: 
	virtual void enterDeleteQueue() = 0;
private:
	void setParentNode(scene::EntityNode* node)
	{
		parent_ = node;
	}

	scene::EntityNode* parent_;

	u32 entflags_;
	u32 entID_; 
};

} // namespace game
} // namespace awrts
#endif//_awrts_BaseEntity_
