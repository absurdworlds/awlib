/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_EntityManager_
#define _hrengin_EntityManager_

#include <hrengin/common/types.h>
#include <hrengin/game/game.h>

namespace hrengin {
class Entity;

//! Entity manager keeps track of entities
class EntityManager {
public:
	//! run entity syncronization, use to update entity position and orientation
	virtual void doSync() = 0;
	//virtual void doCleanup() = 0;

	virtual void addEntity(Entity* entity) = 0;
	virtual void deleteEntity(u32 entid) = 0;
};

HR_GAME_EXP EntityManager* createEntityManager();

} // namespace hrengin
#endif//_hrengin_EntityManager_
