#include "CEntityManager.h"

namespace hrengin
{

CEntityManager::CEntityManager()
{

}

void CEntityManager::doSync()
{
	for(std::vector<IBaseEntity*>::iterator ent = entlist_.begin(); ent != entlist_.end(); ++ent)
	{
		(*ent)->sync();
	}
}

void CEntityManager::doCleanup()
{
	while(!deleteQueue_.empty())
	{
		deleteEntity(deleteQueue_.front());
		deleteQueue_.pop_front();
	}
}

void CEntityManager::addEntity(IBaseEntity* entity)
{
	if(freelist_.empty())
	{
		entlist_.push_back(entity);
	}
	else
	{
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