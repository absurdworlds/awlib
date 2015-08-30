/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Thinking_
#define _awrts_Thinking_

#include <awrts/common/types.h>
#include <awrts/game/Entity.h>

namespace awrts {
namespace game {

class Thinking : public Entity {
public:
	virtual void think(u32 time) = 0;
};

} // namespace game
} // namespace awrts
#endif//_awrts_Thinking_
