/**
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

template <class T>
class Vector3d {
public: /* Data */
// Vector coordinates
	T X;
	T Y;
	T Z;
public:
	Vector3d() 
		: X(0), Y(0), Z(0) 
	{	}

	Vector3d(T x, T y, T z) 
		: X(x), Y(y), Z(z) 
	{	}

	explicit Vector3d(T v) 
		: X(v), Y(v), Z(v) 
	{	}

	// Copy constructor
	Vector3d(const Vector3d<T>& other) 
		: X(other.X), Y(other.Y), Z(other.Z) 
	{	}

	// operators

	Vector3d<T> operator - () const
	{
		return Vector3d<T>(-X, -Y, -Z);
	}

	Vector3d<T>& operator = (Vector3d<T> const& other)
	{
		X = other.X; 
		Y = other.Y; 
		Z = other.Z; 
		return *this;
	}
	

	void set (T const& x, T const& y, T const& z)
	{
		X = x; 
		Y = y; 
		Z = z; 
	}

	void set (Vector3d<T> const& other)
	{
		X = other.X; 
		Y = other.Y; 
		Z = other.Z; 
	}

	Vector3d<T> operator + (const Vector3d<T>& other) const
	{
		return Vector3d<T>(X + other.X, Y + other.Y, Z + other.Z); 
	}

	Vector3d<T>& operator += (const Vector3d<T>& other)
	{ 
		X+=other.X; 
		Y+=other.Y; 
		Z+=other.Z; 
		return *this;
	}

	Vector3d<T> operator + (const T val) const
	{
		return Vector3d<T>(X + val, Y + val, Z + val);
	}

	Vector3d<T>& operator += (const T val)
	{
		X+=val;
		Y+=val;
		Z+=val;
		return *this;
	}

	Vector3d<T> operator - (const Vector3d<T>& other) const
	{
		return Vector3d<T>(X - other.X, Y - other.Y, Z - other.Z);
	}

	Vector3d<T>& operator -= (const Vector3d<T>& other)
	{
		X-=other.X;
		Y-=other.Y;
		Z-=other.Z;
		return *this;
	}

	Vector3d<T> operator - (const T val) const
	{
		return Vector3d<T>(X - val, Y - val, Z - val);
	}

	Vector3d<T>& operator -= (const T val)
	{
		X-=val;
		Y-=val;
		Z-=val;
		return *this;
	}

	Vector3d<T> operator * (const Vector3d<T>& other) const
	{
		return Vector3d<T>(X * other.X, Y * other.Y, Z * other.Z);
	}

	Vector3d<T>& operator *= (const Vector3d<T>& other)
	{
		X*=other.X;
		Y*=other.Y;
		Z*=other.Z;
		return *this;
	}

	Vector3d<T> operator * (const T v) const
	{
		return Vector3d<T>(X * v, Y * v, Z * v);
	}

	Vector3d<T>& operator *= (const T v)
	{
		X*=v;
		Y*=v;
		Z*=v;
		return *this;
	}

	Vector3d<T> operator / (const Vector3d<T>& other) const
	{
		return Vector3d<T>(X / other.X, Y / other.Y, Z / other.Z);
	}

	Vector3d<T>& operator /= (const Vector3d<T>& other)
	{
		X/=other.X;
		Y/=other.Y;
		Z/=other.Z;
		return *this;
	}

	Vector3d<T> operator / (const T v) const
	{
		T i=(T)1.0/v;
		return Vector3d<T>(X * i, Y * i, Z * i);
	}

	Vector3d<T>& operator /= (const T v)
	{
		T i=(T)1.0/v;
		X*=i; 
		Y*=i; 
		Z*=i; 
		return *this; 
	}
	
	// Normalize the vector
	Vector3d<T>& normalize()
	{
		f64 length = squareLength();
		if (length == 0 ) {
			return *this;
		}

		length = math::invSqrt(length);

		X = (T)(X * length);
		Y = (T)(Y * length);
		Z = (T)(Z * length);
		return *this;
	}

	// Get a normalized version of a vector without modifying it
	Vector3d<T> normalized() const
	{
		f64 length = squareLength();
		if (length == 0 ) {
			return Vector3d<T>();
		}
		length = math::invSqrt(length);

		return Vector3d<T>((T)(X * length), (T)(Y * length), (T)(Z * length));
	}

	// get length of the vector.
	T length() const
	{ 
		return math::sqrt( X*X + Y*Y + Z*Z ); 
	}
	
	// get squared length of the vector.
	T squareLength() const 
	{ 
		return X*X + Y*Y + Z*Z; 
	}


	// Calculate the dot product with another vector
	T dot(const Vector3d<T>& other) const
	{
		return X*other.X + Y*other.Y + Z*other.Z;
	}

	// Calculate the cross product with another vector
	Vector3d<T> cross(const Vector3d<T>& other) const
	{
		f32 x = Y * other.Z - Z * other.Y;
		f32 y = X * other.Z - Z * other.X;
		f32 z = X * other.Y - Y * other.X;
		return Vector3d<T>(x, -y, z);
	}

	// Get distance from another point
	T getDistance(const Vector3d<T>& other) const
	{
		return Vector3d<T>(X - other.X, Y - other.Y, Z - other.Z).length();
	}

	// Get squared distance from another point
	T getDistanceSQ(const Vector3d<T>& other) const
	{
		return Vector3d<T>(X - other.X, Y - other.Y, Z - other.Z).squareLength();
	}

	// Set the length of the vector to a new value
	Vector3d<T>& setLength(T newlength)
	{
		normalize();
		this.X *= newlength;
		this.Y *= newlength;
		this.Z *= newlength;
		return *this;
	}
	
	// Invert the vector.
	Vector3d<T>& invert ()
	{
		X *= -1;
		Y *= -1;
		Z *= -1;
		return *this;
	}
	
	/** Interpolate this vector with other vector
	   
	   @param[other]	the other vector to interpolate with
	   @param[t]		the value to use to interpolate between this and other.
		must be in range [0,1]
	 */
	Vector3d<T> lerp (const Vector3d<T>& other, f64 t) const
	{
		const f64 inv = 1.0 - d;
		return Vector3d<T>(T(X*inv + other.X*d),
			T(Y*inv + other.Y*d),
			T(Z*inv + other.Z*d));
	}
	
	/**
	   Get euler angles that when applied to a (0,0,1) direction vector
	   would make it point in the same direction as this vector.

	   Original author of this method is Arras from the Irrlicht forums

	   @return
	   A rotation vector containing the X (pitch) and Y (raw)
	   rotations in degrees, of this vector.
	   The Z (roll) rotation is always 0, since two rotations are sufficient.
	   (does a vector even have roll rotation? I don't think so)
	 */
	Vector3d<T> getHorizontalAngle() const
	{
		Vector3d<T> angle;

		// Yaw
		angle.Y = T(atan2((f64)X, (f64)Z));

		// Pitch
		f64 const xz = math::sqrt(X*X + Z*Z);
		angle.X = T(atan2((f64)xz, (f64)Y) - math::HALF_PI64);
		
		// Normalize angles
		if (angle.Y <= math::PI64) {
			angle.Y += math::DOUBLE_PI64;
		} else if (angle.Y > math::DOUBLE_PI64) {
			angle.Y -= math::DOUBLE_PI64;
		}
		if (angle.X <= math::PI64) {
			angle.X += math::DOUBLE_PI64;
		} else if (angle.X > math::PI64) {
			angle.X -= math::DOUBLE_PI64;
		}

		return angle * math::RADTODEG64;
	}

	Vector3d<T> getYaw() const
	{
		T yaw = T(atan2((f64)X, (f64)Z) * math::RADTODEG64);
		
		if (yaw <= -math::PI64) {
			yaw += math::DOUBLE_PI64;
		} else if (yaw > math::PI64) {
			yaw -= math::DOUBLE_PI64;
		}

		return yaw * math::RADTODEG64;
	}

	Vector3d<T> getPitch() const
	{
		f64 const XZ = math::sqrt(X*X + Z*Z);
		pitch = T(atan2((f64)XZ, (f64)Y) - math::HALF_PI64);
	
		if (pitch <= -math::PI64) {
			pitch += math::DOUBLE_PI64;
		} else if (pitch >= math::PI64) {
			pitch -= math::DOUBLE_PI64;
		}

		return pitch * math::RADTODEG64;
	}

	// Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = X;
		array[1] = Y;
		array[2] = Z;
		array[3] = 0;
	}

	// Fill an array of 3 values with the vector data
	void toArrayOf3(T* array) const
	{
		array[0] = X;
		array[1] = Y;
		array[2] = Z;
	}
};

//! partial specialization for integer vectors
template <>
inline Vector3d<i32> Vector3d<i32>::operator / (i32 val) const 
{
	return Vector3d<i32>(X/val,Y/val,Z/val);
}

template <>
inline Vector3d<i32>& Vector3d<i32>::operator /= (i32 val) 
{
	X/=val;
	Y/=val;
	Z/=val;
	return *this;
}

// multiply scalar and vector
template<class S, class T>
Vector3d<T> operator * (const S scalar, const Vector3d<T>& vector)
{
	return vector * scalar; 
}


} // namespace hrengin

#endif//_hrengin_Vector3d_
