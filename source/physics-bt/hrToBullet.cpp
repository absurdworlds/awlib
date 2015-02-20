/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "hrToBullet.h"

namespace hrengin {
namespace physics {

void quaternionToEuler(btQuaternion const& quat, btVector3& euler) {
	btScalar const W = quat.getW();
	btScalar const X = quat.getX();
	btScalar const Y = quat.getY();
	btScalar const Z = quat.getZ();
	// singularity test
	f32 const test = X*Y + Z*W;
	if (math::equals(test, 0.5f)) { // north pole
		euler.setX(0);
		euler.setY(2 * atan2(X,W));
		euler.setZ(math::HalfPi);
	} else if (math::equals(test, -0.5f)) { // south pole
		euler.setX(0);
		euler.setY(-2 * atan2(X,W));
		euler.setZ(- math::HalfPi);
	} else {
		f32 const sX = X * X;
		f32 const sY = Y * Y;
		f32 const sZ = Z * Z;

		euler.setX(atan2(2*(X*W - Y*Z), 1 - 2*sX - 2*sZ));
		euler.setY(atan2(2*(Y*W - X*Z), 1 - 2*sY - 2*sZ));
		euler.setZ(asin(2*test));
	}

	euler *= math::DegreesInRadian;
}

} // namespace physics
} // namespace hrengin
