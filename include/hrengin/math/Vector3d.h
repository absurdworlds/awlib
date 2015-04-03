/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Vector3d_
#define _hrengin_Vector3d_
#include <array>

#include <hrengin/math/math.h>

namespace hrengin {

//! Represents vector in 3D space
template <class T>
class Vector3d {
public:
	//! Default constructor. Constructs zero vector.
	Vector3d()
		: coord_(),
		x(coord_[0]), y(coord_[1]), z(coord_[2])
	{
	}

	//! Construct vector with same value for coordinates
	explicit Vector3d(T const v)
		: coord_({v, v, v}),
		x(coord_[0]), y(coord_[1]), z(coord_[2])
	{
	}

	//! Construct vector with individual coodrinates
	Vector3d(T const x, T const y, T const z)
		: coord_({x, y, z}),
		x(coord_[0]), y(coord_[1]), z(coord_[2])
	{
	}

	//! Copy constructor
	Vector3d(Vector3d<T> const& other) 
		: coord_({other[0], other[1], other[2]}),
		x(coord_[0]), y(coord_[1]), z(coord_[2])
	{
	}

	//! Predefined instance of zero vector
	static Vector3d<T> const zero;

	//! Set coordinates of the vector
	void set(T const x, T const y, T const z)
	{
		coord_[0] = x;
		coord_[1] = y;
		coord_[2] = z;
	}

	//! Copy coordinates of other vector
	void set(Vector3d<T> const& other)
	{
		coord_[0] = other[0];
		coord_[1] = other[1];
		coord_[2] = other[2];
	}

	//! Copy coordinates of other vector
	Vector3d<T>& operator = (Vector3d<T> const& other)
	{
		set(other);
		return *this;
	}

	//! Vector addition
	Vector3d<T> operator + (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x + other[0], y + other[1], z + other[2]); 
	}

	//! Vector addition
	Vector3d<T>& operator += (Vector3d<T> const& other)
	{ 
		coord_[0] += other[0]; 
		coord_[1] += other[1]; 
		coord_[2] += other[2]; 
		return *this;
	}

	Vector3d<T> operator + (T const val) const
	{
		return Vector3d<T>(x + val, y + val, z + val);
	}

	Vector3d<T>& operator += (T const val)
	{
		coord_[0] += val;
		coord_[1] += val;
		coord_[2] += val;
		return *this;
	}
	Vector3d<T> operator - (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x - other[0], y - other[1], z - other[2]);
	}

	Vector3d<T>& operator -= (Vector3d<T> const& other)
	{
		coord_[0] -= other[0];
		coord_[1] -= other[1];
		coord_[2] -= other[2];
		return *this;
	}

	Vector3d<T> operator - (T const val) const
	{
		return Vector3d<T>(
			coord_[0] - val,
			coord_[1] - val,
			coord_[2] - val);
	}

	Vector3d<T>& operator -= (T const val)
	{
		coord_[0] -= val;
		coord_[1] -= val;
		coord_[2] -= val;
		return *this;
	}

	Vector3d<T> operator * (Vector3d<T> const& other) const
	{
		return Vector3d<T>(
			coord_[0] * other[0],
			coord_[1] * other[1],
			coord_[2] * other[2]);
	}

	Vector3d<T>& operator *= (Vector3d<T> const& other)
	{
		coord_[0] *= other[0];
		coord_[1] *= other[1];
		coord_[2] *= other[2];
		return *this;
	}

	Vector3d<T> operator * (T const v) const
	{
		return Vector3d<T>(x * v, y * v, z * v);
	}

	Vector3d<T>& operator *= (T const v)
	{
		coord_[0] *= v;
		coord_[1] *= v;
		coord_[2] *= v;
		return *this;
	}

	Vector3d<T> operator / (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x / other[0], y / other[1], z / other[2]);
	}

	Vector3d<T>& operator /= (Vector3d<T> const& other)
	{
		coord_[0] /= other[0];
		coord_[1] /= other[1];
		coord_[2] /= other[2];
		return *this;
	}

	Vector3d<T> operator / (T const val) const
	{
		T inv = T(1.0/val);
		return Vector3d<T>(
			coord_[0] * inv,
			coord_[1] * inv,
			coord_[2] * inv);
	}

	Vector3d<T>& operator /= (T const val)
	{
		T const inv = T(1.0/val);
		coord_[0] *= inv; 
		coord_[1] *= inv; 
		coord_[2] *= inv; 
		return *this; 
	}


	Vector3d<T> operator - () const
	{
		return Vector3d<T>(
			-coord_[0],
			-coord_[1],
			-coord_[2]);
	}

	/*!
	 * Check if vectors are identical.
	 * \return
	 * 	`true` if vectors are identical, otherwise `false`.
	 */
	bool operator == (Vector3d<T> const& other) const
	{
		return (math::equals(coord_[0], other[0]) &&
		        math::equals(coord_[1], other[1]) &&
		        math::equals(coord_[2], other[2]));
	}


	//! Normalize the vector
	Vector3d<T>& normalize()
	{
		f64 length = squareLength();
		if (length == 0) {
			return *this;
		}

		length = math::invSqrt(length);

		coord_[0] = T(coord_[0] * length);
		coord_[1] = T(coord_[1] * length);
		coord_[2] = T(coord_[2] * length);

		return *this;
	}

	//! Get a normalized version of a vector without modifying it
	Vector3d<T> normalized() const
	{
		f64 length = squareLength();
		if (length == 0) {
			return Vector3d<T>();
		}

		length = math::invSqrt(length);

		return Vector3d<T>(
			T(coord_[0] * length),
			T(coord_[1] * length),
			T(coord_[2] * length));
	}

	//! Get length of the vector.
	T length() const
	{
		return math::sqrt(
			coord_[0]*coord_[0] +
			coord_[1]*coord_[1] +
			coord_[2]*coord_[2]);
	}

	//! Get squared length of the vector.
	T squareLength() const
	{
		return  coord_[0]*coord_[0] +
			coord_[1]*coord_[1] +
			coord_[2]*coord_[2];
	}

	//! Calculate the dot product with another vector
	T dot(Vector3d<T> const& other) const
	{
		return  coord_[0]*other[0] + 
			coord_[1]*other[1] + 
			coord_[2]*other[2];
	}

	//! Calculate the cross product with another vector
	Vector3d<T> cross(Vector3d<T> const& other) const
	{
		f32 const cx = coord_[1] * other[2] - coord_[2] * other[1];
		f32 const cy = coord_[2] * other[0] - coord_[0] * other[2];
		f32 const cz = coord_[0] * other[1] - coord_[1] * other[0];
		return Vector3d<T>(cx, cy, cz);
	}

	//! Get distance from another point
	T getDistance(Vector3d<T> const& other) const
	{
		return Vector3d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1],
			coord_[2] - other[2]).length();
	}

	//! Get squared distance from another point
	T getDistanceSQ(Vector3d<T> const& other) const
	{
		return Vector3d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1],
			coord_[2] - other[2]).squareLength();
	}

	//! Set the length of the vector to a new value
	Vector3d<T>& setLength(T const newlength)
	{
		normalize();
		coord_[0] *= newlength;
		coord_[1] *= newlength;
		coord_[2] *= newlength;
		return *this;
	}

	// Invert the vector.
	Vector3d<T>& invert()
	{
		coord_[0] *= -1;
		coord_[1] *= -1;
		coord_[2] *= -1;
		return *this;
	}

	/*!
	 * Get euler angles that when applied to a (0,0,1) direction vector
	 * would make it point in the same direction as this vector.
         *
	 * Original author of this method is Arras from the Irrlicht forums
         *
	 * \return
	 *     A rotation vector containing the X (pitch) and Y (raw)
	 *     rotations in degrees, of this vector.
	 *     The Z (roll) rotation is always 0, since two rotations
	 *     are sufficient.
	 *     (does a vector even have roll rotation? I don't think so)
	 */
	Vector3d<T> getHorizontalAngle() const
	{
		Vector3d<T> angle;

		// Yaw
		angle.y = T(atan2(f64(x), f64(z)));

		// Pitch
		f64 const xz = math::sqrt(x*x + z*z);
		angle.x = T(atan2(f64(xz), f64(y)) - math::HalfPi);

		// Normalize angles
		if (angle.y <= -math::Pi) {
			angle.y += math::DoublePi;
		} else if (angle.y > math::Pi) {
			angle.y -= math::DoublePi;
		}
		if (angle.x <= math::Pi) {
			angle.x += math::DoublePi;
		} else if (angle.x > math::Pi) {
			angle.x -= math::DoublePi;
		}

		return math::RadToDeg(angle);
	}

	T getYaw() const
	{
		T yaw = T(atan2(f64(x), f64(z)));

		if (yaw <= -math::Pi) {
			yaw += math::DoublePi;
		} else if (yaw > math::Pi) {
			yaw -= math::DoublePi;
		}

		return math::RadToDeg(yaw);
	}

	T getPitch() const
	{
		f64 const xz = math::sqrt(x*x + z*z);
		T const pitch = T(atan2(f64(xz), f64(y)) - math::HalfPi);

		if (pitch <= -math::Pi) {
			pitch += math::DoublePi;
		} else if (pitch >= math::Pi) {
			pitch -= math::DoublePi;
		}

		return math::RadToDeg(pitch);
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = coord_[0];
		array[1] = coord_[1];
		array[2] = coord_[2];
		array[3] = 0;
	}

	//! Fill an array of 3 values with the vector data
	void toArrayOf3(T* array) const
	{
		array[0] = coord_[0];
		array[1] = coord_[1];
		array[2] = coord_[2];
	}

	//! Access elements of the vector by subscript
	T& operator [] (size_t elem)
	{
		return coord_[elem];
	}

	//! Access elements of the vector by subscript
	T const& operator [] (size_t elem) const
	{
		return coord_[elem];
	}

	//! Get coordinate along X axis
	T& x ()
	{
		return coord_[0];
	}

	//! Get coordinate along Y axis
	T& y ()
	{
		return coord_[1];
	}

	//! Get coordinate along Z axis
	T& z ()
	{
		return coord_[2];
	}

	//! Get coordinate along X axis
	T x () const
	{
		return coord_[0];
	}

	//! Get coordinate along Y axis
	T y () const
	{
		return coord_[1];
	}

	//! Get coordinate along Z axis
	T z () const
	{
		return coord_[2];
	}

private:
	//! Coordinates of the vector
	std::array<T, 3> coord_;
};

// Initialization of static member
template<typename T>
Vector3d<T> const Vector3d<T>::zero = Vector3d(0);


//! Partial specialization for integer vectors
template <>
inline Vector3d<i32> Vector3d<i32>::operator / (i32 const val) const 
{
	return Vector3d<i32>(
		coord_[0]/val,
		coord_[1]/val,
		coord_[2]/val);
}

//! Partial specialization for integer vectors
template <>
inline Vector3d<i32>& Vector3d<i32>::operator /= (i32 const val) 
{
	coord_[0] /= val;
	coord_[1] /= val;
	coord_[2] /= val;
	return *this;
}

//! Multiply scalar and vector
template<class S, class T>
Vector3d<T> operator * (S const scalar, Vector3d<T> const& vector)
{
	return vector * scalar; 
}

/** Interpolate two vectors

	\param v0 The first vector to interpolate
	\param v1 The other vector to interpolate with.
	\param t The value to use to interpolate between v0 and v1
	Must be in range [0,1].
	\return Interpolated vector
 */
template<typename T>
Vector3d<T> lerp (Vector3d<T> const& v0, Vector3d<T> const& v1, f64 t)
{
	return (1.0 - t)*v0 + t*v1;
}

} // namespace hrengin
#endif//_hrengin_Vector3d_
