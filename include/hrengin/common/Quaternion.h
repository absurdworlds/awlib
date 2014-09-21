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

	void set(Quaternion<T> const& other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
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

	T dot (Quaternion<T> const& other)
	{
		return X*other.X + Y*other.Y + Z*other.Z + W*other.W;
	}

	Quaternion<T>& normalize()
	{
		T mag = X*X + Y*Y + Z*Z + W*W;
		if(math::equals(mag, T(1.0))) {
			return *this;
		}

		mag = math::invSqrt(mag);

		X *= mag;
		Y *= mag;
		Z *= mag;
		W *= mag;

		return *this;
	}
	
	T X;
	T Y;
	T Z;
	T W;
};

template <typename T>
Quaternion<T>& lerp (Quaternion<T> const& q0, Quaternion<T> const& q1, f64 t)
{
	
	f64 const inv = 1.0 - t;
	return Quaternion<T>(T(v0.X*inv + v1.X*t),
		T(v0.Y*inv + v1.Y*t),
		T(v0.Z*inv + v1.Z*t),
		T(v0.W*inv + v1.W*t));
}

template <typename T>
Quaternion<T>& nlerp (Quaternion<T> const& q0, Quaternion<T> const& q1, f64 t)
{
	return lerp(q1, q2, t).normalized();
}
template <typename T>
Quaternion<T> slerp (Quaternion<T> const& q1, Quaternion<T> const& q2,
	f64 alpha, f64 threshold = 0.995)
{
	T dot = dot(other);
	
	if(dot > T(threshold)) {
		return lerp(q1, q2, alpha);
	}

	// use shortest path
	if (dot < 0) {
		q1.x = -q1.x;
		q1.y = -q1.y; 
		q1.z = -q1.z;
		dot = -dot;
	}

#if 0 // alternative implementation
	math::clamp(dot, T(-1.0), T(1.0));
	T const theta = acos(dot) * alpha;

	Quaternion<T> q3 = q2 - q1*dot;
	q3.normalize();

	set(q1*sin(theta) + q3*cos(theta))
#else
	T const theta = acos(dot);
	T const rsin = 1/sqrt(1.0 - dot*dot);
	T const t1 = sin((1.0 - alpha)*theta) * rsin;
	T const t2 = sin(alpha*theta) * rsin;
#endif
	return q1*t1 + q2*t2;
}


} // namespace hrengin

#endif//_hrengin_Quaternion_
