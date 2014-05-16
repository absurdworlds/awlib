#ifndef __H_INCLUDED__HRENGIN_IBaseEntity
#define __H_INCLUDED__HRENGIN_IBaseEntity

#include <vector>
#include <algorithm>

#include "Base/hrTypes.h"
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
		for(std::vector<IBaseEntity*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			(*it)->OnParentRemove();
		}
	}
	
	//! get the entity type identifier
	virtual u32 GetEntityIdentifier()
	{
		return ENTID_BaseEntity;
	}

	virtual u32 GetEntityFlag(ENT_FLAG flag)
	{
		return (entflags & flag) != 0;
	}

	//! parent-child thingy
	virtual std::vector<IBaseEntity*>::iterator FindChild(IBaseEntity* child)
	{
		return std::find(children.begin(), children.end(), child);
	}

	//! used in pair to attach one node to another
	virtual bool AttachChild(IBaseEntity* newChild)
	{
		if(FindChild(newChild) != children.end())
		{
			return false;
		}
		else
		{
			newChild->parent = this;
			children.push_back(newChild);
			return true;
		}
	}

	virtual bool SetParent(IBaseEntity* newParent)
	{
		if(parent)
		{
			UnParent();
		}

		return newParent->AttachChild(this);
	}
		
	//! used in pair to detach one node from another
	virtual bool DetachChild(IBaseEntity* child)
	{
		std::vector<IBaseEntity*>::iterator found = FindChild(child);
		if(found != children.end())
		{
			(*found)->parent = 0;
			std::iter_swap(found, children.end()-1);
			children.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual bool UnParent()
	{
		return parent->DetachChild(this);
	}

	/* Virtual methods */

	//! callback: do some action on parent remove
	virtual void OnParentRemove() = 0;

	//! sync all attached nodes and entities
	virtual bool Sync() = 0;

	// Methods to set entity's position and rotation.
	virtual bool SetPosition() = 0;
	virtual bool SetRotation() = 0;
	
protected: /* Methods */
	virtual void EnterDeleteQueue() = 0;
protected: /* Data */
	IBaseEntity*				parent;
	std::vector<IBaseEntity*>	children;

	u32 entflags;

protected:	
	//! make this class uninstanciable
	IBaseEntity() {}

	/// EntID is stored 
	u32 mEntID; 
};

} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IBaseEntity