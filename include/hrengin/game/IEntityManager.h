/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IEntityManager_
#define _hrengin_IEntityManager_

#include <hrengin/common/types.h>
#include <hrengin/game/api.h>

namespace hrengin {

class IBaseEntity;

//! Entity manager keeps track of entities
class IEntityManager {
public:
	//! run entity syncronization, use to update entity position and orientation
	virtual void doSync() = 0;
	//virtual void doCleanup() = 0;

	virtual void addEntity(IBaseEntity* entity) = 0;
	virtual void deleteEntity(u32 entid) = 0;
};

HR_GAME_API IEntityManager* createEntityManager();
	
} // namespace hrengin

#endif//_hrengin_IEntityManager_
