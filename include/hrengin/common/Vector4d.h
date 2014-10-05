/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Vector4d_
#define _hrengin_Vector4d_

#include <hrengin/common/math.h>

namespace hrengin {

//! Represents a 4-dimensional vector
template <class T>
class Vector4d {
public:
	//! Default constructor. Constructs zero vector.
	Vector4d() 
		: x(0), y(0), z(0), w(0)
	{
	}

	//! Construct vector specifying individual coodrinates
	Vector4d(T const x, T const y, T const z, T const w)
		: x(x), y(y), z(z), w(w)
	{
	}

	//! Construct vector with same value for coordinates
	explicit Vector4d(T const v)
		: x(v), y(v), z(v), w(v)
	{
	}

	//! Copy constructor
	Vector4d(Vector4d<T> const& other) 
		: x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	//! Set vector's components
	void set (T const x, T const y, T const z, T const w)
	{
		x = x;
		y = y;
		z = z;
		w = w;
	}

	void set (Vector4d<T> const& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}
	
	Vector4d<T>& operator = (Vector4d<T> const& other)
	{
		set(other);
		return *this;
	}
	
	Vector4d<T> operator + (Vector4d<T> const& other) const
	{
		return Vector4d<T>(w + other.w, x + other.x, y + other.y, z + other.z);
	}

	//! Component-wise addition
	Vector4d<T>& operator += (Vector4d<T> const& other)
	{ 
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vector4d<T> operator + (T const val) const
	{
		return Vector4d<T>(x + val, y + val, z + val, w + val);
	}

	Vector4d<T>& operator += (T const val)
	{
		x += val;
		y += val;
		z += val;
		w += val;
		return *this;
	}
	Vector4d<T> operator - (Vector4d<T> const& other) const
	{
		return Vector4d<T>(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4d<T>& operator -= (Vector4d<T> const& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vector4d<T> operator - (T const val) const
	{
		return Vector4d<T>(x - val, y - val, z - val, w - val);
	}

	Vector4d<T>& operator -= (T const val)
	{
		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	Vector4d<T> operator * (Vector4d<T> const& other) const
	{
		return Vector4d<T>(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	Vector4d<T>& operator *= (Vector4d<T> const& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vector4d<T> operator * (T const v) const
	{
		return Vector4d<T>(x * v, y * v, z * v, w * v);
	}

	Vector4d<T>& operator *= (T const v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
		return *this;
	}

	Vector4d<T> operator / (Vector4d<T> const& other) const
	{
		return Vector4d<T>(x / other.x, y / other.y, z / other.z, w / other.w);
	}

	Vector4d<T>& operator /= (Vector4d<T> const& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	Vector4d<T> operator / (T const val) const
	{
		T inv = T(1.0/val);
		return Vector4d<T>(x * inv, y * inv, z * inv, w * inv);
	}

	Vector4d<T>& operator /= (T const val)
	{
		T const inv = T(1.0/val);
		x *= inv; 
		y *= inv; 
		z *= inv; 
		w *= inv; 
		return *this; 
	}
	

	Vector4d<T> operator - () const
	{
		return Vector4d<T>(-x, -y, -z, -w);
	}

	
	//! Normalize the vector
	Vector4d<T>& normalize()
	{
		f64 length = squareLength();
		if (length == 0) {
			return *this;
		}

		length = math::invSqrt(length);

		x = T(x * length);
		y = T(y * length);
		z = T(z * length);
		w = T(w * length);

		return *this;
	}

	//! Get a normalized version of a vector without modifying it
	Vector4d<T> normalized() const
	{
		f64 length = squareLength();
		if (length == 0) {
			return Vector4d<T>();
		}

		length = math::invSqrt(length);

		return Vector4d<T>(T(x * length), T(y * length),
			T(z * length), T(w * length));
	}

	//! Get length of the vector.
	T length() const
	{ 
		return math::sqrt( x*x + y*y + z*z + w*w );
	}
	
	//! Get squared length of the vector.
	T squareLength() const
	{ 
		return x*x + y*y + z*z + w*w;
	}

	//! Calculate the dot product with another vector
	T dot(Vector4d<T> const& other) const
	{
		return x*other.x + y*other.y + z*other.z + w*other.w;
	}

	//! Get distance from another point
	T getDistance(Vector4d<T> const& other) const
	{
		return Vector4d<T>(x - other.x, y - other.y,
			z - other.z, w - other.w).length();
	}

	//! Get squared distance from another point
	T getDistanceSQ(Vector4d<T> const& other) const
	{
		return Vector4d<T>(x - other.x, y - other.y,
			z - other.z, w - other.w).squareLength();
	}

	//! Set the length of the vector to a new value
	Vector4d<T>& setLength(T const newlength)
	{
		normalize();
		this.x *= newlength;
		this.y *= newlength;
		this.z *= newlength;
		this.w *= newlength;
		return *this;
	}
	
	// Invert the vector.
	Vector4d<T>& invert ()
	{
		x *= -1;
		y *= -1;
		z *= -1;
		w *= -1;
		return *this;
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = x;
		array[1] = y;
		array[2] = z;
		array[3] = w;
	}

	//! First component
	T x;
	//! Second component
	T y;
	//! Third component
	T z;
	//! Fourth component
	T w;
};

//! Partial specialization for integer vectors
//! Divide integer vector by scalar
template <>
inline Vector4d<i32> Vector4d<i32>::operator / (i32 const val) const 
{
	return Vector4d<i32>(x/val, y/val, z/val, w/val);
}

//! Partial specialization for integer vectors
//! Divide integer vector by scalar
template <>
inline Vector4d<i32>& Vector4d<i32>::operator /= (i32 const val) 
{
	x /= val;
	y /= val;
	z /= val;
	w /= val;
	return *this;
}

//! Multiply scalar and vector
template<class S, class T>
Vector4d<T> operator * (S const scalar, Vector4d<T> const& vector)
{
	return vector * scalar; 
}

/*! Interpolate two vectors
	\param v0 The first vector to interpolate
	\param v1 The other vector to interpolate with.
	\param t The value to use to interpolate between v0 and v1
	Must be in range [0,1].
	\return Interpolated vector
 */
template<typename T>
Vector4d<T> lerp (Vector4d<T> const& v0, Vector4d<T> const& v1, f64 t)
{
	return (1.0 - t)*v0 + t*v1;
}

} // namespace hrengin

#endif//_hrengin_Vector4d_
