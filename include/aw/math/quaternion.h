/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO wARRANTy, to the extent permitted by law.
 */
#ifndef aw_math_quaternion_h
#define aw_math_quaternion_h
//#include <complex>
#include <aw/math/equals.h>
#include <aw/math/math.h>
#include <aw/math/vector3d.h>
#include <aw/math/vector4d.h>
namespace aw {
namespace math {
//! Quaternion for representing rotations
template<typename T>
struct quaternion {
	/*! Default constructor
	\brief Represents zero rotation.
	 */
	quaternion()
		: w(1), x(0), y(0), z(0)
	{
	}

	/*! Constructor
	\brief Construct quaternion using individual components.
	 */
	quaternion(T const w, T const x, T const y, T const z)
		: w(w), x(x), y(y), z(z)
	{
	}

	/*! Constructor
	 * \brief Construct quaternion from euler angles.
	 */
	static quaternion<T> euler(T const pitch, T const yaw, T const roll)
	{
		return quaternion<T>{}.setEuler(pitch, yaw, roll);
	}

	/*! Constructor
	 * \brief Construct quaternion using axis and rotation around given axis.
	 */
	static quaternion<T> axis_angle(vector3d<T> const& axis, T const angle)
	{
		return quaternion<T>{}.setAxisAngle(axis, angle);
	}

	//! Copy components from other quaternion
	quaternion<T>& operator=(quaternion<T> const& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}


	//! Get a result of component-wise addition of two quaternions
	quaternion<T> operator+(quaternion<T> const& other) const
	{
		return {w + other.w, x + other.x, y + other.y, z + other.z};
	}

	//! Component-wise addition
	quaternion<T>& operator+=(quaternion<T> const& other)
	{ 
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	quaternion<T> operator+(T const val) const
	{
		return {w + val, x + val, y + val, z + val};
	}

	quaternion<T>& operator+=(T const val)
	{
		x += val;
		y += val;
		z += val;
		w += val;
		return *this;
	}

	//! Get a result of component-wise subtraction of two quaternions
	quaternion<T> operator-(quaternion<T> const& other) const
	{
		return {w - other.w, x - other.x, y - other.y, z - other.z};
	}

	//! Component-wise subtraction
	quaternion<T>& operator-=(quaternion<T> const& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	quaternion<T> operator-(T const val) const
	{
		return {w - val, x - val, y - val, z - val};
	}

	quaternion<T>& operator-=(T const val)
	{
		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	quaternion<T> operator-() const
	{
		return {-w, -x, -y, -z};
	}

	//! Quaternion multiplication
	quaternion<T>& operator*=(quaternion<T> const& other)
	{
		x = (x * other.w) + (w * other.x) + (z * other.y) - (y * other.z);
		y = (y * other.w) - (z * other.x) + (w * other.y) + (x * other.z);
		z = (z * other.w) + (y * other.x) - (x * other.y) + (w * other.z);
		w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);

		return *this;
	}

	quaternion<T> operator*(T const val) const
	{
		return {w*val, x*val, y*val, z*val};
	}

	quaternion<T>& operator*=(T const val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}

	//! Set quaternion from euler angles
	quaternion<T>& set_euler(T x, T y, T z)
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

	quaternion<T>& set_axis_angle(vector3d<T> const& axis, T angle)
	{
		angle /= T(2.0);
		angle *= math::radians_in_degree;

		vector3d<T> const v = axis.normalized() * sin(angle);

		set(cos(angle), v.x, v.y, v.z);

		return *this;
	}

	//! Get quaternion as euler angles
	auto to_euler()
	{
		vector3d<T> euler = {};

		// singularity test
		f32 const test = x*y + z*w;
		if (math::equals(test, 0.5f)) { // north pole
			euler.x = 0;
			euler.y = 2 * atan2(x, w);
			euler.z = math::half_pi;
		} else if (math::equals(test, -0.5f)) { // south pole
			euler.x = 0;
			euler.y = -2 * atan2(x,w);
			euler.z = -math::half_pi;
		} else {
			f32 const sX = x * x;
			f32 const sY = y * y;
			f32 const sZ = z * z;

			euler.x = atan2(2*(x*w - y*z) , 1 - 2*sX - 2*sZ);
			euler.y = atan2(2*(y*w - x*z) , 1 - 2*sY - 2*sZ);
			euler.z = asin(2*test);
		}

		euler *= math::degrees_in_radian;

		return euler.to_tuple();
	}

	//! Get quaternion in axis-angle representation
	std::tuple<vector3d<T>, T> toAxisAngle()
	{
		vector3d<T> axis = {};
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

		return {axis, angle};
	}

	//! Calculate dot product with other quaternion
	T dot(quaternion<T> const& other) const
	{
		return x*other.x + y*other.y + z*other.z + w*other.w;
	}

	T magnitude_sq() const
	{
		return dot(*this);
	}

	T magnitude() const
	{
		return math::sqrt(magnitude_sq());
	}

	//! Normalize quaternion
	quaternion<T>& normalize()
	{
		T const sqrMag = magnitude_sq();

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
quaternion<T> operator*(S const scalar, quaternion<T> const& quat)
{
	return quat * scalar;
}

//! Multiply two quaternions
template <typename T>
quaternion<T> operator*(quaternion<T> q0, quaternion<T> const& q1)
{
	return q0 *= q1;
}

//! Get normalized quaterion
template <typename T>
quaternion<T> normalize(quaternion<T> const& quat)
{
	return quaternion<T>{quat}.normalize();
}

//! Linear interpolation of quaternion
template <typename T>
quaternion<T>& lerp(quaternion<T> const& q0, quaternion<T> const& q1, f64 t)
{
	return (1-t)*q0 + t*q1;
}

template <typename T>
quaternion<T> nlerp(quaternion<T> const& q0, quaternion<T> const& q1, f64 t)
{
	return lerp(q0, q1, t).normalize();
}

template <typename T>
quaternion<T> slerp(quaternion<T> const& q0, quaternion<T> const& q1,
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

	quaternion<T> q2 = q1 - q0*dot;
	q2.normalize();

	return sin(theta)*q0 + cos(theta)*q2;
#endif
}
} // namespace math
} // namespace aw
#endif//aw_math_quaternion_h
