/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_DebugDrawer_
#define _awrts_DebugDrawer_

#include <awrts/common/hidden_impl.h>

//#include <awrts/graphics/Renderable.h>
#include <awrts/graphics/RenderingDevice.h>

namespace awrts {
namespace physics {
class PhysicsWorld;

class DebugDrawer /*: public IRenderable*/ {
public:
	virtual void render() = 0;

	virtual void setWorld(PhysicsWorld* world) = 0;

	//! Internal implementation details
	DECLARE_HIDDEN_DETAILS(DebugDrawer);
};

} // namespace graphics
} // namespace awrts
#endif //_awrts_DebugDrawer_
