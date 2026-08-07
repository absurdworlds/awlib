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
template<typename T>
struct axis_angle {
	vector3d<T> axis;
	T angle;
};

/*!
 * Unit quaternion representing a rotation in 3D space.
 *
 * Conventions, chosen to match `aw::math::matrix3`:
 *
 *  - Rotations are right-handed and act on column vectors,
 *    applied as `v' = q·v·conjugate(q)` (see `rotate`).
 *  - Multiplication is the Hamilton product, so `a * b` denotes
 *    the rotation `b` followed by the rotation `a`, in the same
 *    order as the equivalent matrix product `A * B`.
 *  - Euler angles are `pitch` around the X axis, `yaw` around the
 *    Y axis and `roll` around the Z axis, in radians, composed as
 *    `roll * yaw * pitch` — the order used by `matrix_from_euler`.
 */
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
	static quaternion<T> from_euler(T const pitch, T const yaw, T const roll)
	{
		return quaternion<T>{}.set_euler(pitch, yaw, roll);
	}

	/*! Constructor
	 * \brief Construct quaternion using axis and rotation around given axis.
	 */
	static quaternion<T> from_axis_angle(vector3d<T> const& axis, T const angle)
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
		return *this;
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

	/*! Quaternion (Hamilton) multiplication
	 * \brief Rotate by \a other first, then by this quaternion.
	 */
	quaternion<T>& operator*=(quaternion<T> const& other)
	{
		auto old_x = x, old_y = y, old_z = z, old_w = w;

		x = (old_w * other.x) + (old_x * other.w) + (old_y * other.z) - (old_z * other.y);
		y = (old_w * other.y) - (old_x * other.z) + (old_y * other.w) + (old_z * other.x);
		z = (old_w * other.z) + (old_x * other.y) - (old_y * other.x) + (old_z * other.w);
		w = (old_w * other.w) - (old_x * other.x) - (old_y * other.y) - (old_z * other.z);

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

	//! Set quaternion from individual components
	quaternion<T>& set(T const w, T const x, T const y, T const z)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

	/*! Set quaternion from euler angles (in radians)
	 * \brief Rotate by \a roll around Z, then \a yaw around Y,
	 *        then \a pitch around X.
	 */
	quaternion<T>& set_euler(T pitch, T yaw, T roll)
	{
		vector3d<T> vec{ pitch, yaw, roll };
		vec /= T(2);

		vector3d<T> const s = sin( vec );
		vector3d<T> const c = cos( vec );

		x = c.z() * c.y() * s.x() - s.z() * s.y() * c.x();
		y = c.z() * s.y() * c.x() + s.z() * c.y() * s.x();
		z = s.z() * c.y() * c.x() - c.z() * s.y() * s.x();
		w = c.z() * c.y() * c.x() + s.z() * s.y() * s.x();
		return *this;
	}

	quaternion<T>& set_axis_angle(vector3d<T> const& axis, T angle)
	{
		angle /= T(2);

		vector3d<T> const v = math::normalize(axis) * T(std::sin(angle));

		set(T(std::cos(angle)), v.x(), v.y(), v.z());

		return *this;
	}

	/*! Get quaternion as euler angles (in radians)
	 * \return Vector holding the rotation around the X axis (pitch)
	 *         in its x component, around Y (yaw) in y, and around Z
	 *         (roll) in z — the layout accepted by `matrix_from_euler`.
	 */
	vector3d<T> to_euler() const
	{
		/*
		 * Recovering (roll ± pitch) instead of each angle on its own
		 * keeps the extraction well-conditioned at yaw = ±90°, where
		 * the two are no longer individually defined (gimbal lock).
		 */
		T const sum  = T( 2 * std::atan2(x + z, w - y) ); // roll + pitch
		T const diff = T( 2 * std::atan2(z - x, w + y) ); // roll − pitch

		// |cos(yaw/2) ± sin(yaw/2)|, whose ratio is tan(π/4 + yaw/2)
		T const cs = T( std::hypot(w + y, z - x) );
		T const cd = T( std::hypot(w - y, x + z) );

		vector3d<T> euler = {};

		euler[axis::x] = (sum - diff) / T(2);
		euler[axis::y] = T( 2 * std::atan2(cs, cd) - pi/2 );
		euler[axis::z] = (sum + diff) / T(2);

		return euler;
	}

	//! Get quaternion in axis-angle representation
	axis_angle<T> to_axis_angle() const
	{
		vector3d<T> axis = {};
		T angle = {};

		T const tCos = w;
		T tSin = x*x + y*y + z*z;

		if (tSin > T{0}) {
			tSin = T(math::sqrt(tSin));
			T invSin = 1 / tSin;

			angle = T( 2 * std::atan2(tSin, tCos) );
			axis.x() = x * invSin;
			axis.y() = y * invSin;
			axis.z() = z * invSin;
		} else {
			axis.x() = T{0};
			axis.y() = T{0};
			axis.z() = T{-1};
			angle    = T{0};
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
			T const mag = math::sqrt(sqrMag);

			x /= mag;
			y /= mag;
			z /= mag;
			w /= mag;
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

//! Get the conjugate, which for a unit quaternion is the inverse rotation
template <typename T>
quaternion<T> conjugate(quaternion<T> const& quat)
{
	return {quat.w, -quat.x, -quat.y, -quat.z};
}

//! Rotate a vector by a unit quaternion: `v' = q·v·conjugate(q)`
template <typename T>
vector3d<T> rotate(quaternion<T> const& quat, vector3d<T> const& vec)
{
	vector3d<T> const axis{ quat.x, quat.y, quat.z };
	vector3d<T> const tmp = T(2) * cross(axis, vec);

	return vec + quat.w * tmp + cross(axis, tmp);
}

//! Linear interpolation of quaternion
template <typename T>
quaternion<T> lerp(quaternion<T> const& q0, quaternion<T> const& q1, f64 t)
{
	return (1-t)*q0 + t*q1;
}

template <typename T>
quaternion<T> nlerp(quaternion<T> const& q0, quaternion<T> const& q1, f64 t)
{
	return lerp(q0, q1, t).normalize();
}

template <typename T>
quaternion<T> slerp(quaternion<T> q0, quaternion<T> const& q1,
	f64 alpha, bool shortest)
{
	T tCos = q0.dot(q1);

	// use shortest path
	if (tCos < 0 && shortest) {
		q0 = -q0;
		tCos = -tCos;
	}

	constexpr T epsilon = T(0.005);
	if(tCos > (1 - epsilon)) {
		return nlerp(q0, q1, alpha);
	}

	T const tSin = T(std::sqrt(1.0 - tCos*tCos));
	T const theta = T(std::atan2(tSin, tCos));

	T const invSin = 1/tSin;
	T const t1 = T(std::sin((1.0 - alpha)*theta)) * invSin;
	T const t2 = T(std::sin(alpha*theta)) * invSin;

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
