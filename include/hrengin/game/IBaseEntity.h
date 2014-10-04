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
//#include "Base/IVirtualObject.h"

namespace hrengin {

const u32 ENTID_Invalid = 0;
const u32 ENTID_BaseEntity = 'base';

enum EntFlag : u32 {
};

//! Base for game entities
class IBaseEntity {
public:
	virtual ~IBaseEntity()
	{
		for(auto it = children_.begin(); it != children_.end(); ++it) {
			(*it)->onParentRemove();
		}
	}
	
	//! get the entity type identifier
	virtual u32 getEntityIdentifier()
	{
		return ENTID_BaseEntity;
	}

	virtual bool getEntityFlag(EntFlag flag)
	{
		return (entflags & flag) != 0;
	}

	//! parent-child thingy
	virtual std::vector<IBaseEntity*>::iterator findChild(IBaseEntity* child)
	{
		return std::find(children_.begin(), children_.end(), child);
	}

	//! used in pair to attach one node to another
	virtual bool attachChild(IBaseEntity* newChild)
	{
		if(findChild(newChild) != children_.end()) {
			return false;
		} else {
			newChild->parent_ = this;
			children_.push_back(newChild);
			return true;
		}
	}

	virtual bool setParent(IBaseEntity* newParent)
	{
		if(parent_) {
			unParent();
		}

		return newParent->attachChild(this);
	}
		
	//! used in pair to detach one node from another
	virtual bool detachChild(IBaseEntity* child)
	{
		std::vector<IBaseEntity*>::iterator found = findChild(child);
		if(found != children_.end()) {
			(*found)->parent_ = 0;
			std::iter_swap(found, children_.end()-1);
			children_.pop_back();
			return true;
		} else {
			return false;
		}
	}

	virtual bool unParent()
	{
		return parent_->detachChild(this);
	}

	// called on parent's removal
	virtual void onParentRemove() = 0;

	// sync all attached nodes and entities
	virtual void sync() = 0;

	// set entity's position
	virtual void setPosition(Vector3d<f32> position) = 0;
	// set entity's rotation
	virtual void setRotation(Vector3d<f32> rotation) = 0;

	virtual Vector3d<f32> getPosition() const = 0;
	virtual Vector3d<f32> getRotation() const = 0;
	
protected: /* Methods */
	virtual void enterDeleteQueue() = 0;
protected: /* Data */
	IBaseEntity*			parent_;
	std::vector<IBaseEntity*>	children_;

	u32 entflags;

protected:
	// EntID is stored 
	u32 mEntID; 
};

} // namespace hrengin

#endif//_hrengin_IBaseEntity_
