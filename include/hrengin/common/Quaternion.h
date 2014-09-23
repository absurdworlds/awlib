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
		: W(1.0), X(0.0), Y(0.0), Z(0.0)
	{
	}
	
	//! Constructor
	/*!
	\brief Construct quaternion using individual components.
	 */
	Quaternion(T const W, T const X, T const Y, T const Z)
		: W(W), X(X), Y(Y), Z(Z)
	{
	}
	
	//! Constructor
	/*!
	\brief Construct quaternion from euler angles.
	 */
	Quaternion(T const pitch, T const yaw, T const roll)
	{
		setEuler(pitch, yaw, roll);
	}

	//! Constructor
	/*!
	\brief Construct quaternion from euler angles.
	 */
	Quaternion(Vector3d<T> const& euler)
	{
		setEuler(euler.X, euler.Y, euler.Z);
	}
	
	//! Constructor
	/*!
	\brief Construct quaternion using axis and rotation around given axis.
	 */
	Quaternion(Vector3d<T> const& axis, T const angle)
	{
		setAxisAngle(axis, angle);
	}

	//! Set quaternion by individual components
	void set(T const w, T const x, T const y, T const z)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	//! Copy components from other quaternion
	void set(Quaternion<T> const& other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
	}
	
	Quaternion<T> operator + (Quaternion<T> const& other) const
	{
		return Quaternion<T>(W + other.W, X + other.X, Y + other.Y, Z + other.Z); 
	}

	Quaternion<T>& operator += (Quaternion<T> const& other)
	{ 
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		W += other.W;
		return *this;
	}

	Quaternion<T> operator + (T const val) const
	{
		return Quaternion<T>(W + val, X + val, Y + val, Z + val);
	}

	Quaternion<T>& operator += (T const val)
	{
		X += val;
		Y += val;
		Z += val;
		W += val;
		return *this;
	}

	Quaternion<T> operator - (Quaternion<T> const& other) const
	{
		return Quaternion<T>(W - other.W, X - other.X, Y - other.Y, Z - other.Z);
	}

	Quaternion<T>& operator -= (Quaternion<T> const& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		W -= other.W;
		return *this;
	}
	
	Quaternion<T> operator - (T const val) const
	{
		return Quaternion<T>(W - val, X - val, Y - val, Z - val);
	}

	Quaternion<T>& operator -= (T const val)
	{
		X -= val;
		Y -= val;
		Z -= val;
		W -= val;
		return *this;
	}

	Quaternion<T> operator - () const
	{
		return Quaternion<T>(-W, -X, -Y, -Z);
	}
	
	Quaternion<T> operator * (Quaternion<T> const& other) const
	{
		Quaternion<T> q0;

		q0.X = (X * other.W) + (W * other.X) + (Z * other.Y) - (Y * other.Z);
		q0.Y = (Y * other.W) - (Z * other.X) + (W * other.Y) + (X * other.Z);
		q0.Z = (Z * other.W) + (Y * other.X) - (X * other.Y) + (W * other.Z);
		q0.W = (W * other.W) - (X * other.X) - (Y * other.Y) - (Z * other.Z);

		return q0;
	}
	
	Quaternion<T>& operator *= (Quaternion<T> const& other)
	{
		X = (X * other.W) + (W * other.X) + (Z * other.Y) - (Y * other.Z);
		Y = (Y * other.W) - (Z * other.X) + (W * other.Y) + (X * other.Z);
		Z = (Z * other.W) + (Y * other.X) - (X * other.Y) + (W * other.Z);
		W = (W * other.W) - (X * other.X) - (Y * other.Y) - (Z * other.Z);

		return *this;
	}
	
	Quaternion<T> operator * (T const val) const
	{
		return Quaternion<T>(W*val, X*val, Y*val, Z*val);
	}
	
	Quaternion<T>& operator *= (T const val)
	{
		X *= val;
		Y *= val;
		Z *= val;
		W *= val;

		return *this;
	}

	//! Set quaternion from euler angles
	void setEuler(T x, T y, T z)
	{
		x *= T(0.5 * math::DEGTORAD64);
		y *= T(0.5 * math::DEGTORAD64);
		z *= T(0.5 * math::DEGTORAD64);

		T const sx = sin(x);
		T const cx = sin(x);

		T const sy = sin(y);
		T const cy = sin(y);

		T const sz = sin(z);
		T const cz = sin(z);

		X = sx*sy*cz + cx*cy*sz;
		Y = sx*cy*cz + cx*sy*sz;
		Z = cx*sy*cz - sx*cy*sz;
		W = cx*cy*cz - sx*sy*sz;
	}
	
	void setAxisAngle(Vector3d<T> const& axis, T angle)
	{
		angle /= T(2.0);
		angle *= math::DEGTORAD64;

		Vector3d<T> const v = axis.normalized() * sin(angle);

		set(cos(angle), v.X, v.Y, v.Z);
	}

	//! Get quaternion as euler angles
	void toEuler(Vector3d<T>& euler)
	{
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

		euler *= math::RADTODEG64;
	}
	
	//! Get quaternion in axis-angle representation
	void toAxisAngle(Vector3d<T>& axis, T& angle) const
	{
		T const tCos = W;
		T tSin = T(1.0) - W*W;
		// T tSin = X*X + Y*Y + Z*Z;

		if(tSin > T(0.0)) {
			tSin = T(sqrt(tSin));
			T invSin = 1 / tSin;
			
			angle = T(2.0 * atan2(tSin, tCos));
			axis.X = X * invSin;
			axis.Y = Y * invSin;
			axis.Z = Z * invSin;
		} else {
			axis.X = T(0.0);
			axis.Y = T(1.0);
			axis.Z = T(0.0);
			angle = T(0.0);
		}
	}


	T dot (Quaternion<T> const& other)
	{
		return X*other.X + Y*other.Y + Z*other.Z + W*other.W;
	}

	Quaternion<T>& normalize()
	{
		T const sqrMag = X*X + Y*Y + Z*Z + W*W;
		
		if(!math::equals(sqrMag, T(1.0))) {
			T const invMag = math::invSqrt(sqrMag);

			X *= invMag;
			Y *= invMag;
			Z *= invMag;
			W *= invMag;
		}

		return *this;
	}
	
	Quaternion<T> normalized() const
	{
		T const sqrMag = X*X + Y*Y + Z*Z + W*W;
		
		if(!math::equals(sqrMag, T(1.0))) {
			T const invMag = math::invSqrt(sqrMag);

			return Quaternion<T>(T(X*invMag),
				T(Y*invMag), T(Z*invMag), T(W*invMag));
		}

		return Quaternion<T>();
	}

	T X;
	T Y;
	T Z;
	T W;
};


//! Multiply quaternion by scalar
template<class S, class T>
Quaternion<T> operator * (S const scalar, Quaternion<T> const& quat)
{
	return quat * scalar; 
}

template <typename T>
Quaternion<T>& lerp (Quaternion<T> const& q0, Quaternion<T> const& q1, f64 t)
{
	return (1-t)*q0 + t*q1;
}

template <typename T>
Quaternion<T> nlerp (Quaternion<T> const& q0, Quaternion<T> const& q1, f64 t)
{
	return lerp(q0, q1, t).normalize();
}

template <typename T>
Quaternion<T> slerp (Quaternion<T> const& q0, Quaternion<T> const& q1,
	f64 alpha, bool shortest)
{
	T tCos = q0.dot(q1);

	// use shortest path
	if (tCos < 0 && shortest) {
		q0 = -q0;
		dot = -dot;
	}

	static T const epsilon = T(0.005);
	if(tCos > (1 - epsilon)) {
		return nlerp(q0, q1, alpha);
	}

	T const tSin = sqrt(1.0 - tCos*tCos);
	T const theta = atan2(tSin, tCos);
	
	T const invSin = 1/tSin;
	T const t1 = sin((1.0 - alpha)*theta) * invSin;
	T const t2 = sin(alpha*theta) * invSin;

	return t1*q0 + t2*q1;

#if 0 // alternative implementation
	math::clamp(dot, T(-1.0), T(1.0));
	T const theta = acos(dot) * alpha;

	Quaternion<T> q2 = q1 - q0*dot;
	q2.normalize();

	return sin(theta)*q0 + cos(theta)*q2;
#endif
}


} // namespace hrengin

#endif//_hrengin_Quaternion_
