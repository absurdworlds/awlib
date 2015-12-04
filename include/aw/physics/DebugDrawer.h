/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_DebugDrawer_
#define _aw_DebugDrawer_
#include <aw/utility/hidden_impl.h>

//#include <aw/graphics/Renderable.h>
#include <aw/graphics/RenderingDevice.h>

namespace aw {
namespace physics {
class PhysicsWorld;

class DebugDrawer /*: public IRenderable*/ {
public:
	virtual DebugDrawer() = default;

	virtual void render() = 0;

	virtual void setWorld(PhysicsWorld* world) = 0;

	//! Internal implementation details
	DECLARE_HIDDEN_DETAILS(DebugDrawer);
};

} // namespace graphics
} // namespace aw
#endif //_aw_DebugDrawer_
