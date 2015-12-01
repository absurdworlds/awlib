/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_EventManager_
#define _aw_EventManager_
#include <aw/common/types.h>
#include <awrts/game/game.h>

namespace aw {
namespace game {
class Thinking;
typedef void (*EventCallback) (u32);

typedef struct {
	union {
		Thinking* owner;
		EventCallback callback;
	};
	u32 nextFire;
	u32 period;
	bool isActive : 1;
	bool isCallback : 1;
} Event;

//! Dispatches game events
class EventManager {
	//virtual u32 addEvent(EventCallback event, u32 period) = 0;
	public:
		virtual u32 addEvent(Event event) = 0;
		virtual void removeEvent(u32 eventId) = 0;
		virtual void advance() = 0;
};

AW_GAME_EXP EventManager* createEventManager();

} // namespace game
} // namespace aw
#endif//_aw_EventManager_
