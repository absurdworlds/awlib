/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
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
