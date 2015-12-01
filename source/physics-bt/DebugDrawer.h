/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_DebugDrawer_impl_
#define _aw_DebugDrawer_impl_

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <aw/common/types.h>

#include <aw/physics/DebugDrawer.h>
#include "PhysicsWorld.h"

namespace aw {
namespace physics {
namespace bullet {

class DebugDraw : public btIDebugDraw {
public:
	DebugDraw(graphics::RenderingDevice* renderer);

	void drawLine(const btVector3& from, const btVector3& to,
		const btVector3& color);

	void drawContactPoint(const btVector3& PointOnB,
		const btVector3& normalOnB, btScalar distance, int lifeTime,
		const btVector3& color);

	void reportErrorWarning(const char* text);

	void draw3dText(const btVector3& location, const char* text) { }

	void setDebugMode(int mode);
	int getDebugMode() const;

private:
	DebugDraw(const DebugDraw& other) = delete;

	int mode;
	graphics::RenderingDevice * vmgr_;
};
} // namespace bullet

class DebugDrawer::Details {
public:
	Details(graphics::RenderingDevice* renderer)
		//: drawer(renderer)
	{
		debugDraw = new bullet::DebugDraw(renderer);
		// temporary
		debugDraw->setDebugMode(
			btIDebugDraw::DBG_DrawWireframe |
			btIDebugDraw::DBG_DrawAabb |
			btIDebugDraw::DBG_DrawContactPoints |
			//btIDebugDraw::DBG_DrawText |
			//btIDebugDraw::DBG_DrawConstraintLimits |
			btIDebugDraw::DBG_DrawConstraints //|
		);
	}
	btIDebugDraw* debugDraw;
};

namespace bullet {
class DebugDrawer : public physics::DebugDrawer {
public:
	DebugDrawer(graphics::RenderingDevice* renderer)
		: details_(renderer)
	{
		//details_.drawer = new DebugDraw(renderer);
	}
	virtual void render()
	{
		// temporary, until tendering tools are implemented
		world_->debugDrawWorld();
	}

	virtual void setWorld(physics::PhysicsWorld* world)
	{
		world_ = world->getDetails()->world;
		world_->setDebugDrawer(details_.debugDraw);
	}

	// for internal use only
	virtual DebugDrawer::Details* getDetails()
	{
		return &details_;
	}
private:
	DebugDrawer::Details details_;
	btDynamicsWorld* world_;
};

} // namespace bullet
} // namespace physics
} // namespace aw
#endif//_aw_DebugDrawer_impl_
