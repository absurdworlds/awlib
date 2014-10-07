/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Vector3d_
#define _hrengin_Vector3d_

#include <hrengin/common/math.h>

namespace hrengin {

//! Represents vector in 3D space
template <class T>
class Vector3d {
public:
	//! Default constructor. Constructs zero vector.
	Vector3d() 
		: x(0), y(0), z(0) 
	{
	}
	
	//! Construct vector with individual coodrinates
	Vector3d(T const x, T const y, T const z) 
		: x(x), y(y), z(z) 
	{
	}

	//! Construct vector with same value for coordinates
	explicit Vector3d(T const v) 
		: x(v), y(v), z(v) 
	{
	}

	//! Copy constructor
	Vector3d(Vector3d<T> const& other) 
		: x(other.x), y(other.y), z(other.z) 
	{
	}

	//! Construct zero vector
	static Vector3d<T> zero()
	{
		return Vector3d;
	}

	void set (T const x, T const y, T const z)
	{
		x = x; 
		y = y; 
		z = z; 
	}

	void set (Vector3d<T> const& other)
	{
		x = other.x; 
		y = other.y; 
		z = other.z; 
	}

	
	Vector3d<T>& operator = (Vector3d<T> const& other)
	{
		x = other.x; 
		y = other.y; 
		z = other.z; 
		return *this;
	}
	
	Vector3d<T> operator + (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x + other.x, y + other.y, z + other.z); 
	}

	Vector3d<T>& operator += (Vector3d<T> const& other)
	{ 
		x += other.x; 
		y += other.y; 
		z += other.z; 
		return *this;
	}

	Vector3d<T> operator + (T const val) const
	{
		return Vector3d<T>(x + val, y + val, z + val);
	}

	Vector3d<T>& operator += (T const val)
	{
		x += val;
		y += val;
		z += val;
		return *this;
	}
	Vector3d<T> operator - (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x - other.x, y - other.y, z - other.z);
	}

	Vector3d<T>& operator -= (Vector3d<T> const& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3d<T> operator - (T const val) const
	{
		return Vector3d<T>(x - val, y - val, z - val);
	}

	Vector3d<T>& operator -= (T const val)
	{
		x -= val;
		y -= val;
		z -= val;
		return *this;
	}

	Vector3d<T> operator * (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x * other.x, y * other.y, z * other.z);
	}

	Vector3d<T>& operator *= (Vector3d<T> const& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3d<T> operator * (T const v) const
	{
		return Vector3d<T>(x * v, y * v, z * v);
	}

	Vector3d<T>& operator *= (T const v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vector3d<T> operator / (Vector3d<T> const& other) const
	{
		return Vector3d<T>(x / other.x, y / other.y, z / other.z);
	}

	Vector3d<T>& operator /= (Vector3d<T> const& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vector3d<T> operator / (T const val) const
	{
		T inv = T(1.0/val);
		return Vector3d<T>(x * inv, y * inv, z * inv);
	}

	Vector3d<T>& operator /= (T const val)
	{
		T const inv = T(1.0/val);
		x *= inv; 
		y *= inv; 
		z *= inv; 
		return *this; 
	}
	

	Vector3d<T> operator - () const
	{
		return Vector3d<T>(-x, -y, -z);
	}

	
	//! Normalize the vector
	Vector3d<T>& normalize()
	{
		f64 length = squareLength();
		if (length == 0) {
			return *this;
		}

		length = math::invSqrt(length);

		x = T(x * length);
		y = T(y * length);
		z = T(z * length);

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

		return Vector3d<T>(T(x * length), T(y * length), T(z * length));
	}

	//! Get length of the vector.
	T length() const
	{ 
		return math::sqrt( x*x + y*y + z*z ); 
	}
	
	//! Get squared length of the vector.
	T squareLength() const
	{ 
		return x*x + y*y + z*z; 
	}


	//! Calculate the dot product with another vector
	T dot(Vector3d<T> const& other) const
	{
		return x*other.x + y*other.y + z*other.z;
	}

	//! Calculate the cross product with another vector
	Vector3d<T> cross(Vector3d<T> const& other) const
	{
		f32 x = y * other.z - z * other.y;
		f32 y = z * other.x - x * other.z;
		f32 z = x * other.y - y * other.x;
		return Vector3d<T>(x, y, z);
	}

	//! Get distance from another point
	T getDistance(Vector3d<T> const& other) const
	{
		return Vector3d<T>(x - other.x, y - other.y, z - other.z).length();
	}

	//! Get squared distance from another point
	T getDistanceSQ(Vector3d<T> const& other) const
	{
		return Vector3d<T>(x - other.x, y - other.y, z - other.z).squareLength();
	}

	//! Set the length of the vector to a new value
	Vector3d<T>& setLength(T const newlength)
	{
		normalize();
		this.x *= newlength;
		this.y *= newlength;
		this.z *= newlength;
		return *this;
	}
	
	// Invert the vector.
	Vector3d<T>& invert ()
	{
		x *= -1;
		y *= -1;
		z *= -1;
		return *this;
	}
	
	/*!
	   Get euler angles that when applied to a (0,0,1) direction vector
	   would make it point in the same direction as this vector.

	   Original author of this method is Arras from the Irrlicht forums

	   \return
	   A rotation vector containing the X (pitch) and Y (raw)
	   rotations in degrees, of this vector.
	   The Z (roll) rotation is always 0, since two rotations are sufficient.
	   (does a vector even have roll rotation? I don't think so)
	 */
	Vector3d<T> getHorizontalAngle() const
	{
		Vector3d<T> angle;

		// Yaw
		angle.y = T(atan2(f64(x), f64(z)));

		// Pitch
		f64 const xz = math::sqrt(x*x + z*z);
		angle.x = T(atan2(f64(xz), f64(y)) - math::HALF_PI64);
		
		// Normalize angles
		if (angle.y <= -math::PI64) {
			angle.y += math::DOUBLE_PI64;
		} else if (angle.y > math::PI64) {
			angle.y -= math::DOUBLE_PI64;
		}
		if (angle.x <= math::PI64) {
			angle.x += math::DOUBLE_PI64;
		} else if (angle.x > math::PI64) {
			angle.x -= math::DOUBLE_PI64;
		}

		return angle * math::RADTODEG64;
	}

	T getYaw() const
	{
		T yaw = T(atan2(f64(x), f64(z)));
		
		if (yaw <= -math::PI64) {
			yaw += math::DOUBLE_PI64;
		} else if (yaw > math::PI64) {
			yaw -= math::DOUBLE_PI64;
		}

		return yaw * math::RADTODEG64;
	}

	T getPitch() const
	{
		f64 const xz = math::sqrt(x*x + z*z);
		T const pitch = T(atan2(f64(xz), f64(y)) - math::HALF_PI64);
	
		if (pitch <= -math::PI64) {
			pitch += math::DOUBLE_PI64;
		} else if (pitch >= math::PI64) {
			pitch -= math::DOUBLE_PI64;
		}

		return pitch * math::RADTODEG64;
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = x;
		array[1] = y;
		array[2] = z;
		array[3] = 0;
	}

	//! Fill an array of 3 values with the vector data
	void toArrayOf3(T* array) const
	{
		array[0] = x;
		array[1] = y;
		array[2] = z;
	}

	//! Coordinate along X axis
	T x;
	//! Coordinate along Y axis
	T y;
	//! Coordinate along Z axis
	T z;
};

//! Partial specialization for integer vectors
template <>
inline Vector3d<i32> Vector3d<i32>::operator / (i32 const val) const 
{
	return Vector3d<i32>(x/val, y/val, z/val);
}

//! Partial specialization for integer vectors
template <>
inline Vector3d<i32>& Vector3d<i32>::operator /= (i32 const val) 
{
	x /= val;
	y /= val;
	z /= val;
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
