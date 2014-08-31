
#include "CEventManager.h"

namespace hrengin {
HRENGIN_API IEventManager* createEventManager()
{
	return new CEventManager();
}
} // namespace hrengin
