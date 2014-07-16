#ifndef __H_INCLUDED__HRENGIN_IBaseEntity
#define __H_INCLUDED__HRENGIN_IBaseEntity

#include <vector>
#include <algorithm>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector3d.h>
//#include "Base/IVirtualObject.h"

namespace hrengin
{
	
const u32 ENTID_Invalid = 0;
const u32 ENTID_BaseEntity = 1;

enum ENT_FLAG
{
	ENTFLAG_Someflag = 1,
};

class IBaseEntity
{
public:
	virtual ~IBaseEntity()
	{
		for(std::vector<IBaseEntity*>::iterator it = children_.begin(); it != children_.end(); ++it)
		{
			(*it)->onParentRemove();
		}
	}
	
	//! get the entity type identifier
	virtual u32 getEntityIdentifier()
	{
		return ENTID_BaseEntity;
	}

	virtual u32 getEntityFlag(ENT_FLAG flag)
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
		if(findChild(newChild) != children_.end())
		{
			return false;
		}
		else
		{
			newChild->parent_ = this;
			children_.push_back(newChild);
			return true;
		}
	}

	virtual bool setParent(IBaseEntity* newParent)
	{
		if(parent_)
		{
			unParent();
		}

		return newParent->attachChild(this);
	}
		
	//! used in pair to detach one node from another
	virtual bool detachChild(IBaseEntity* child)
	{
		std::vector<IBaseEntity*>::iterator found = findChild(child);
		if(found != children_.end())
		{
			(*found)->parent_ = 0;
			std::iter_swap(found, children_.end()-1);
			children_.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual bool unParent()
	{
		return parent_->detachChild(this);
	}

	/* Virtual methods */

	//! callback: do some action on parent remove
	virtual void onParentRemove() = 0;

	//! sync all attached nodes and entities
	virtual void sync() = 0;

	// Methods to set entity's position and rotation.
	virtual void setPosition(Vector3d position) = 0;
	virtual void setRotation(Vector3d rotation) = 0; //LATER: replace with quaternions
	
protected: /* Methods */
	virtual void enterDeleteQueue() = 0;
protected: /* Data */
	IBaseEntity*				parent_;
	std::vector<IBaseEntity*>	children_;

	u32 entflags;

protected:	
	//! make this class uninstanciable
	IBaseEntity() {}

	/// EntID is stored 
	u32 mEntID; 
};

} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IBaseEntity