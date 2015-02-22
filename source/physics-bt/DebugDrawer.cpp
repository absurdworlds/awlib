/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/common/types.h>

#include "DebugDrawer.h"

namespace hrengin {
namespace physics {
namespace bullet {

DebugDraw::DebugDraw(graphics::RenderingDevice* renderer)
	: mode(DBG_NoDebug), vmgr_(renderer)
{

}

void DebugDraw::drawLine(btVector3 const& from, btVector3 const& to, btVector3 const& color)
{
	//workaround to bullet's inconsistent debug colors which are
	// either from 0.0 - 1.0 or from 0.0 - 255.0

	Vector3d<f32> newColor;

	if (color[0] <= 1.0 && color[0] > 0.0) {
		newColor[0] = ((u32)(color[0]*255.0));
	}
	if (color[1] <= 1.0 && color[1] > 0.0) {
		newColor[1] = ((u32)(color[1]*255.0));
	}
	if (color[2] <= 1.0 && color[2] > 0.0) {
		newColor[2] = ((u32)(color[2]*255.0));
	}

	vmgr_->drawLine(
		Vector3d<f32>(from[0], from[1], from[2]),
		Vector3d<f32>(to[0], to[1], to[2]),
		newColor);
}

void DebugDraw::drawContactPoint(btVector3 const& PointOnB, btVector3 const& normalOnB, btScalar distance, int lifeTime, btVector3 const& color)
{
	//this->drawLine(PointOnB, PointOnB + normalOnB*distance, ONTACTPOINT_OLOR);

	btVector3 const to(PointOnB + normalOnB*distance);

	vmgr_->drawLine(
		Vector3d<f32>(PointOnB[0], PointOnB[1], PointOnB[2]),
		Vector3d<f32>(to[0], to[1], to[2]),
		Vector3d<f32>(255.0,255.0,255.0));
}

void DebugDraw::reportErrorWarning(char const* text)
{
	//this->logger->log(text, irr::ELL_ERROR);
}

//void DebugDraw::draw3dText(btVector3 const& location, char const* text) { }

void DebugDraw::setDebugMode(int mode)
{
	this->mode = mode;
}

int DebugDraw::getDebugMode() const
{
	return this->mode;
}
} // namespace bullet
} // namespace physics
} // namespace hrengin
