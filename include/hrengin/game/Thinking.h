/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Thinking_
#define _hrengin_Thinking_

#include <hrengin/common/types.h>
#include <hrengin/game/Entity.h>

namespace hrengin {
namespace game {

class Thinking : public Entity {
public:
	virtual void think(u32 time) = 0;
};

} // namespace game
} // namespace hrengin
#endif//_hrengin_Thinking_
