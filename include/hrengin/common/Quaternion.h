/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Quaternion_
#define _hrengin_Quaternion_

//#include <complex>

#include <hrengin/common/math.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {

template<typename T>
class Quaternion {
public:
	//! Default constructor
	/*!
	\brief Represents zero rotation.
	 */
	Quaternion()
		: X(0.0), Y(0.0), Z(0.0), W(1.0)
	{
	}
	
	//! Constructor
	/*!
	\brief Construct quaternion using individual components.
	 */
	Quaternion(T const& X, T const& Y, T const& Z, T const& W)
		: X(X), Y(Y), Z(Z), W(W)
	{
	}
	
	//! Constructor
	/*!
	\brief Construct quaternion from euler angles.
	 */
	Quaternion(T const& pitch, T const& yaw, T const& roll)
	{
		setEuler(pitch, yaw, roll);
	}

	//! Constructor
	/*!
	\brief Construct quaternion from euler angles.
	 */
	Quaternion(Vector3d<T> const& euler)
	{
	}
	
	//! Constructor
	/*!
	\brief Construct quaternion using axis and rotation around given axis.
	 */
	Quaternion(Vector3d<T> const& axis, T const& rotation)
	{
	}

	Quaternion<T>& setEuler(T x, T y, T z)
	{
	
	}
	
	//! Get quaternion as euler angles
	Vector3d<T> getEuler()
	{
		Vector3d euler;
		// singularity test
		f32 const test = X*Y + Z*W;
		if (math::equals(test, 0.5f)) { // north pole
			euler.X = 0;
			euler.Y = 2 * atan2(X, W);
			euler.Z = math::HALF_PI64;
		} else if (math::equals(test, -0.5f)) { // south pole
			euler.X = 0;
			euler.Y = -2 * atan2(X,W);
			euler.Z = -math::HALF_PI64;
		} else {
			f32 const sX = X * X;
			f32 const sY = Y * Y;
			f32 const sZ = Z * Z;
		
			euler.X = atan2(2*(X*W - Y*Z) , 1 - 2*sX - 2*sZ);
			euler.Y = atan2(2*(Y*W - X*Z) , 1 - 2*sY - 2*sZ);
			euler.Z = asin(2*test);
		}

		return euler * math::RADTODEG64;
	}

	T X;
	T Y;
	T Z;
	T W;
};

} // namespace hrengin

#endif//_hrengin_Quaternion_
