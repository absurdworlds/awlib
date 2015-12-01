/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "EventManager.h"

namespace aw {
namespace game {
AW_GAME_EXP EventManager* createEventManager()
{
	return new impl_::EventManager();
}

void impl_::EventManager::advance()
{
	u32 time = aw::getTime();

	for (auto event = events_.begin(); event != events_.end(); ++event) {
		if ((*event).nextFire <= time) {
			(*event).owner->think((*event).nextFire);
			(*event).nextFire =  (*event).nextFire + (*event).period;
		}
	}
}
} // namespace game
} // namespace aw
