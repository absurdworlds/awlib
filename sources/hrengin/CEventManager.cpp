
#include "CEventManager.h"

namespace hrengin {
HRENGIN_API IEventManager& getEventManager()
{
	static CEventManager singleton;
	return singleton;
}
}