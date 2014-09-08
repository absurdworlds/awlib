/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IEntityManager_
#define _hrengin_IEntityManager_

#include <hrengin/common/types.h>
#include <hrengin/common/api.h>

namespace hrengin {

class IBaseEntity;

class IEntityManager {
public:
	// run entity syncronization, snaps all entity components to new positions
	virtual void doSync() = 0;
	//virtual void doCleanup() = 0;

	virtual void addEntity(IBaseEntity* entity) = 0;
	virtual void deleteEntity(u32 entid) = 0;
};

HRENGIN_API IEntityManager* createEntityManager();
	
} // namespace hrengin

#endif//_hrengin_IEntityManager_
