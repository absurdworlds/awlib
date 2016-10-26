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
#include <aw/math/vector_funcs.h>
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
		: w{w}, x{x}, y{y}, z{z}
	{
	}

	/*! Constructor
	 * \brief Construct quaternion from euler angles.
	 */
	static quaternion<T> euler(T const pitch, T const yaw, T const roll)
	{
		return quaternion<T>{}.set_euler(pitch, yaw, roll);
	}

	/*! Constructor
	 * \brief Construct quaternion using axis and rotation around given axis.
	 */
	static quaternion<T> axis_angle(vector3d<T> const& axis, T const angle)
	{
		return quaternion<T>{}.set_axis_angle(axis, angle);
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
	quaternion<T>& set_euler(T pitch, T yaw, T roll)
	{
		vector3d<T> vec{ pitch, yaw, roll };
		vec /= T(2);

		vector3d<T> const s = sin( vec );
		vector3d<T> const c = cos( vec );

		x = s.x() * s.y() * c.z() + c.x() * c.y() * s.z();
		y = s.x() * c.y() * c.z() + c.x() * s.y() * s.z();
		z = c.x() * s.y() * c.z() - s.x() * c.y() * s.z();
		w = c.x() * c.y() * c.z() - s.x() * s.y() * s.z();
		return *this;
	}

	quaternion<T>& set_axis_angle(vector3d<T> const& axis, T angle)
	{
		angle /= T(2);

		vector3d<T> const v = axis.normalized() * sin(angle);

		set(cos(angle), v.x(), v.y(), v.z());

		return *this;
	}

	//! Get quaternion as euler angles
	vector3d<T> to_euler()
	{
		vector3d<T> euler = {};

		// singularity test
		T const xyzw = x*y + z*w;
		if ( math::equals(xyzw, 0.5f) ) { // north pole
			euler[axis::x] = math::half_pi;
			euler[axis::y] = 2 * atan2(x, w);
			euler[axis::z] = 0;
		} else if ( math::equals(xyzw, -0.5f) ) { // south pole
			euler[axis::x] = -math::half_pi;
			euler[axis::y] = -2 * atan2(x, w);
			euler[axis::z] = 0;
		} else {
			T const sX = x * x;
			T const sY = y * y;
			T const sZ = z * z;

			euler[axis::x] = asin(2*xyzw);
			euler[axis::y] = atan2(2*(x*w - y*z), 1 - 2*sX - 2*sZ);
			euler[axis::z] = atan2(2*(y*w - x*z), 1 - 2*sY - 2*sZ);
		}

		return euler;
	}

	//! Get quaternion in axis-angle representation
	std::tuple<vector3d<T>, T> to_axis_angle()
	{
		vector3d<T> axis = {};
		T angle = {};

		T const tCos = w;
		T tSin = T{1} - w*w;
		// T tSin = x*x + y*y + z*z;

		if (tSin > T{0}) {
			tSin = T(sqrt(tSin));
			T invSin = 1 / tSin;

			angle = T( 2 * atan2(tSin, tCos) );
			axis.x = x * invSin;
			axis.y = y * invSin;
			axis.z = z * invSin;
		} else {
			axis.x = T{0};
			axis.y = T{0};
			axis.z = T{-1};
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
