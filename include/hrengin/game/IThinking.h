#ifndef _hrengin_IThinking_
#define _hrengin_IThinking_

#include <hrengin/common/types.h>
#include <hrengin/game/IBaseEntity.h>

namespace hrengin {

class IThinking : public IBaseEntity {
public:
	virtual void think(u32 time) = 0;
};

} // namespace hrengin

#endif//_hrengin_IThinking_