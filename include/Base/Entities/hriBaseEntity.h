
#ifndef __HG_hriBaseEntity__
#define __HG_hriBaseEntity__

#include "Base/hrTypes.h"
#include <vector>
#include <algorithm>

namespace hrengin
{
	
const u32 ENTID_Invalid = 0;
const u32 ENTID_BaseEntity = 1;

enum ENT_FLAG
{
	ENTFLAG_Someflag = 1,
};

class hriBaseEntity
{
public:
	virtual ~hriBaseEntity()
	{
		for(std::vector<hriBaseEntity*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			(*it)->OnParentRemove();
		}
	}

	//! sync all attached nodes and entities
	virtual bool Sync() = 0;
	
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
	virtual std::vector<hriBaseEntity*>::iterator FindChild(hriBaseEntity* child)
	{
		return std::find(children.begin(), children.end(), child);
	}

	//! used in pair to attach one node to another
	virtual bool AttachChild(hriBaseEntity* newChild)
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

	virtual bool SetParent(hriBaseEntity* newParent)
	{
		if(parent)
		{
			UnParent();
		}

		return newParent->AttachChild(this);
	}
		
	//! used in pair to detach one node from another
	virtual bool DetachChild(hriBaseEntity* child)
	{
		std::vector<hriBaseEntity*>::iterator found = FindChild(child);
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


protected:
	virtual void EnterDeleteQueue() = 0;
	virtual void OnParentRemove() = 0;

	hriBaseEntity*				parent;
	std::vector<hriBaseEntity*>	children;

	u32 entflags;

protected:	
	//! make this class uninstanciable
	hriBaseEntity() {}
};

} // namespace hrengin

#endif//__HG_hriBaseEntity__