/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IEventManager_
#define _hrengin_IEventManager_

#include <hrengin/common/types.h>
#include <hrengin/game/api.h>

namespace hrengin {
class IThinking;
typedef void (*EventCallback) (u32);

typedef struct {
	union {
		IThinking* owner;
		EventCallback callback;
	};
	u32 nextFire;
	u32 period;
	bool isActive : 1;
	bool isCallback : 1;
} Event;

//! Dispatches game events
class IEventManager {
	//virtual u32 addEvent(EventCallback event, u32 period) = 0;
	public:
		virtual u32 addEvent(Event event) = 0;
		virtual void removeEvent(u32 eventId) = 0;
		virtual void advance() = 0;
};

HR_GAME_API IEventManager* createEventManager();

} // namespace hrengin
#endif//_hrengin_IEventManager_
