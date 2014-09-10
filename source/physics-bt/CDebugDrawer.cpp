/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <Bullet/btBulletDynamicsCommon.h>

#include <hrengin/common/types.h>
#include <hrengin/graphics/IRenderingDevice.h>

namespace hrengin {
namespace physics {

class DebugDraw : public btIDebugDraw {
public:
	DebugDraw(graphics::IRenderingDevice* renderer)
	 : mode(DBG_NoDebug), vmgr_(renderer)
	{

	}

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		//workaround to bullet's inconsistent debug colors which are either from 0.0 - 1.0 or from 0.0 - 255.0

		Vector3d<f32> newColor;

		if (color[0] <= 1.0 && color[0] > 0.0) {
			newColor.X = ((u32)(color[0]*255.0));
		}
		if (color[1] <= 1.0 && color[1] > 0.0) {
			newColor.Y = ((u32)(color[1]*255.0));
		}
		if (color[2] <= 1.0 && color[2] > 0.0) {
			newColor.Z = ((u32)(color[2]*255.0));
		}

		vmgr_->drawLine(
		Vector3d<f32>(from[0], from[1], from[2]),
		Vector3d<f32>(to[0], to[1], to[2]),
		newColor);
	}
	

	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
		//   this->drawLine(PointOnB, PointOnB + normalOnB*distance, CONTACTPOINT_COLOR);

		const btVector3 to(PointOnB + normalOnB*distance);

		vmgr_->drawLine(
			Vector3d<f32>(PointOnB[0], PointOnB[1], PointOnB[2]),
			Vector3d<f32>(to[0], to[1], to[2]),
			Vector3d<f32>(255.0,255.0,255.0));
	}

	void reportErrorWarning(const char* text)
	{
		//this->logger->log(text, irr::ELL_ERROR);
	}

	void draw3dText(const btVector3& location, const char* text) { }

	void setDebugMode(int mode) { this->mode = mode; }

	int getDebugMode() const { return this->mode; }

private:
	DebugDraw(const DebugDraw& other) = delete;

	int mode;
	graphics::IRenderingDevice * vmgr_;
};


} // namespace physics
} // namespace hrengin
