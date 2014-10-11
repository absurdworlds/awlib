/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IBaseEntity_
#define _hrengin_IBaseEntity_

#include <vector>
#include <algorithm>

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

#include <hrengin/scene/IEntityNode.h>
//#include "Base/IVirtualObject.h"

namespace hrengin {

const u32 ENTID_Invalid = 0;
const u32 ENTID_BaseEntity = 0x62617365; // 'base'

enum EntFlag : u32 {
};

//! Base for game entities
class IEntity {
	friend class scene::IEntityNode;
public:
	virtual ~IEntity() {
		
	}
	
	//! get the entity type identifier
	virtual u32 getEntityIdentifier()
	{
		return ENTID_BaseEntity;
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
	void setParentNode (scene::IEntityNode* node)
	{
		parent_ = node;
	}
	
	scene::IEntityNode*	parent_;

	u32 entflags_;
	u32 entID_; 
};

} // namespace hrengin

#endif//_hrengin_IBaseEntity_
