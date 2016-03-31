/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO wARRANTy, to the extent permitted by law.
 */
#ifndef _aw_Quaternion_
#define _aw_Quaternion_
//#include <complex>
#include <aw/math/math.h>
#include <aw/math/equals.h>
#include <aw/math/Vector3d.h>
#include <aw/math/Vector4d.h>
namespace aw {
//! Quaternion for representing rotations
template<typename T>
class Quaternion {
public:
	/*! Default constructor
	\brief Represents zero rotation.
	 */
	Quaternion()
		: w(1.0), x(0.0), y(0.0), z(0.0)
	{
	}

	/*! Constructor
	\brief Construct quaternion using individual components.
	 */
	Quaternion(T const w, T const x, T const y, T const z)
		: w(w), x(x), y(y), z(z)
	{
	}

	/*! Constructor
	 * \brief Construct quaternion from euler angles.
	 */
	static Quaternion<T> euler(T const pitch, T const yaw, T const roll)
	{
		return Quaternion<T>{}.setEuler(pitch, yaw, roll);
	}

	/*! Constructor
	 * \brief Construct quaternion using axis and rotation around given axis.
	 */
	static Quaternion<T> axisAngle(Vector3d<T> const& axis, T const angle)
	{
		return Quaternion<T>{}.setAxisAngle(axis, angle);
	}

	//! Copy components from other quaternion
	Quaternion<T>& operator =(Quaternion<T> const& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}


	//! Get a result of component-wise addition of two quaternions
	Quaternion<T> operator + (Quaternion<T> const& other) const
	{
		return {w + other.w, x + other.x, y + other.y, z + other.z};
	}

	//! Component-wise addition
	Quaternion<T>& operator += (Quaternion<T> const& other)
	{ 
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Quaternion<T> operator + (T const val) const
	{
		return {w + val, x + val, y + val, z + val};
	}

	Quaternion<T>& operator += (T const val)
	{
		x += val;
		y += val;
		z += val;
		w += val;
		return *this;
	}

	//! Get a result of component-wise subtraction of two quaternions
	Quaternion<T> operator - (Quaternion<T> const& other) const
	{
		return {w - other.w, x - other.x, y - other.y, z - other.z};
	}

	//! Component-wise subtraction
	Quaternion<T>& operator -= (Quaternion<T> const& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Quaternion<T> operator - (T const val) const
	{
		return {w - val, x - val, y - val, z - val};
	}

	Quaternion<T>& operator -= (T const val)
	{
		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	Quaternion<T> operator - () const
	{
		return {-w, -x, -y, -z};
	}

	//! Quaternion multiplication
	Quaternion<T> operator * (Quaternion<T> const& other) const
	{
		Quaternion<T> q0;
		return q0 *= other;
	}

	Quaternion<T>& operator *= (Quaternion<T> const& other)
	{
		x = (x * other.w) + (w * other.x) + (z * other.y) - (y * other.z);
		y = (y * other.w) - (z * other.x) + (w * other.y) + (x * other.z);
		z = (z * other.w) + (y * other.x) - (x * other.y) + (w * other.z);
		w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);

		return *this;
	}

	Quaternion<T> operator * (T const val) const
	{
		return {w*val, x*val, y*val, z*val};
	}

	Quaternion<T>& operator *= (T const val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;

		return *this;
	}

	//! Set quaternion from euler angles
	Quaternion<T>& setEuler(T x, T y, T z)
	{
		x *= T(math::degToRad(0.5));
		y *= T(math::degToRad(0.5));
		z *= T(math::degToRad(0.5));

		T const sx = sin(x);
		T const cx = sin(x);

		T const sy = sin(y);
		T const cy = sin(y);

		T const sz = sin(z);
		T const cz = sin(z);

		x = sx*sy*cz + cx*cy*sz;
		y = sx*cy*cz + cx*sy*sz;
		z = cx*sy*cz - sx*cy*sz;
		w = cx*cy*cz - sx*sy*sz;

		return *this;
	}

	Quaternion<T>& setAxisAngle(Vector3d<T> const& axis, T angle)
	{
		angle /= T(2.0);
		angle *= math::RadiansInDegree;

		Vector3d<T> const v = axis.normalized() * sin(angle);

		set(cos(angle), v.x, v.y, v.z);

		return *this;
	}

	//! Get quaternion as euler angles
	auto toEuler()
	{
		Vector3d<T> euler = {};

		// singularity test
		f32 const test = x*y + z*w;
		if (math::equals(test, 0.5f)) { // north pole
			euler.x = 0;
			euler.y = 2 * atan2(x, w);
			euler.z = math::HalfPi;
		} else if (math::equals(test, -0.5f)) { // south pole
			euler.x = 0;
			euler.y = -2 * atan2(x,w);
			euler.z = -math::HalfPi;
		} else {
			f32 const sX = x * x;
			f32 const sY = y * y;
			f32 const sZ = z * z;

			euler.x = atan2(2*(x*w - y*z) , 1 - 2*sX - 2*sZ);
			euler.y = atan2(2*(y*w - x*z) , 1 - 2*sY - 2*sZ);
			euler.z = asin(2*test);
		}

		euler *= math::DegreesInRadian;

		return euler.to_tuple();
	}

	//! Get quaternion in axis-angle representation
	std::tuple<Vector3d<T>, T> toAxisAngle()
	{
		Vector3d<T> axis = {};
		T angle = {};

		T const tCos = w;
		T tSin = T{1} - w*w;
		// T tSin = x*x + y*y + z*z;

		if (tSin > T{0}) {
			tSin = T(sqrt(tSin));
			T invSin = 1 / tSin;

			angle = T(math::radToDeg(2 * atan2(tSin, tCos)));
			axis.x = x * invSin;
			axis.y = y * invSin;
			axis.z = z * invSin;
		} else {
			axis.x = T{0};
			axis.y = T{1};
			axis.z = T{0};
			angle  = T{0};
		}

		return {axis, angle}
	}

	//! Calculate dot product with other quaternion
	T dot(Quaternion<T> const& other) const
	{
		return x*other.x + y*other.y + z*other.z + w*other.w;
	}

	T magnitudeSq() const
	{
		return dot(*this);
	}

	T magnitude() const
	{
		return math::sqrt(magnitudeSq());
	}

	//! Normalize quaternion
	Quaternion<T>& normalize()
	{
		T const sqrMag = magnitudeSq();

		if (!math::equals(sqrMag, T{1})) {
			T const invMag = math::invSqrt(sqrMag);

			x *= invMag;
			y *= invMag;
			z *= invMag;
			w *= invMag;
		}

		return *this;
	}


	//! Scalar component
	T w;
	//! First vector component
	T x;
	//! Second vector component
	T y;
	//! Third vector component
	T z;
};


//! Multiply quaternion by scalar
template<class S, class T>
Quaternion<T> operator * (S const scalar, Quaternion<T> const& quat)
{
	return quat * scalar;
}

//! Get normalized quaterion
Quaternion<T> normalize(Quaternion<T> const& quat)
{
	return Quaternion<T>{quat}.normalize();
}

//! Linear interpolation of quaternion
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
		tCos = -tCos;
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
} // namespace aw
#endif//_aw_Quaternion_
