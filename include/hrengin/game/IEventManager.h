#ifndef _hrengin_IEventManager_
#define _hrengin_IEventManager_

#include <hrengin/common/types.h>
#include <hrengin/common/api.h>

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

class IEventManager {
	//virtual u32 addEvent(EventCallback event, u32 period) = 0;
	public:
		virtual u32 addEvent(Event event) = 0;
		virtual void removeEvent(u32 eventId) = 0;
		virtual void advance() = 0;
};

HRENGIN_API IEventManager& getEventManager();
} //end namespace hrengin

#endif//_hrengin_IEventManager_
