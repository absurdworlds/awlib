/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include "CEntityManager.h"

namespace hrengin {
HRENGIN_API IEntityManager* createEntityManager()
{
	return new CEntityManager();
}

CEntityManager::CEntityManager()
{

}

void CEntityManager::doSync()
{
	for(std::deque<IBaseEntity*>::iterator ent = entlist_.begin(); ent != entlist_.end(); ++ent) {
		(*ent)->sync();
	}
}

void CEntityManager::addEntity(IBaseEntity* entity)
{
	if(freelist_.empty()) {
		entlist_.push_back(entity);
	} else {
		u32 freeCell = freelist_.back();
		freelist_.pop_back();
		entlist_[freeCell] = entity;
	}
}

void CEntityManager::deleteEntity(u32 entid)
{
	delete entlist_[entid];
	entlist_[entid] = &nullEntity;
	freelist_.push_back(entid);
}
} // namespace hrengin
