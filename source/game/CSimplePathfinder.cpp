#include "CSimplePathfinder.h"

namespace hrengin {
namespace ai {

HRENGIN_API IBasePathfinder* createSimplePathfinder()
{
	return new CSimplePathfinder;
}

}
}