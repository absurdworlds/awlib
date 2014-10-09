/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Vector2d_
#define _hrengin_Vector2d_

#include <hrengin/common/types.h>
#include <hrengin/common/math.h>

namespace hrengin {

//! Represents positions and directions in 2D space
template <typename T>
class Vector2d {
public:
	Vector2d() 
		: x(0), y(0) 
	{
	}

	Vector2d(T x, T y) 
		: x(x), y(y) 
	{
	}
	
	//! Construct vector with same both coordinates 
	explicit Vector2d(T v) 
		: x(v), y(v) 
	{
	}

	//! Copy constructor
	Vector2d(Vector2d<T> const& other) 
		: x(other.x), y(other.y)
	{
	}
	
	//! Predefined instance of zero vector
	static Vector2d<T> const zero;

	Vector2d<T>& operator = (Vector2d<T> const& other)
	{
		x = other.x; 
		y = other.y; 
		return *this; 
	}

	Vector2d<T> operator - () const 
	{
		return Vector2d<T>(-x, -y);
	}

	
	Vector2d<T> operator + (Vector2d<T> const& other) const 
	{
		return Vector2d<T>(x + other.x, y + other.y);
	}

	Vector2d<T>& operator += (Vector2d<T> const& other) 
	{
		x += other.x; 
		y += other.y; 
		return *this; 
	}

	Vector2d<T> operator - (Vector2d<T> const& other) const 
	{ 
		return Vector2d<T>(x - other.x, y - other.y); 
	}

	Vector2d<T>& operator -= (Vector2d<T> const& other) 
	{ 
		x -= other.x; 
		y -= other.y; 
		return *this; 
	}

	Vector2d<T> operator - (T const v) const 
	{ 
		return Vector2d<T>(x - v, y - v); 
	}

	Vector2d<T>& operator -= (T const v) 
	{ 
		x -= v; 
		y -= v; 
		return *this; 
	}

	Vector2d<T> operator * (Vector2d<T> const& other) const 
	{ 
		return Vector2d<T>(x * other.x, y * other.y); 
	}

	Vector2d<T>& operator *= (Vector2d<T> const& other) 
	{ 
		x *= other.x; 
		y *= other.y; 
		return *this; 
	}

	Vector2d<T> operator * (const T v) const
	{ 
		return Vector2d<T>(x * v, y * v);
	}

	Vector2d<T>& operator *= (const T v) 
	{
		x *= v; 
		y *= v; 
		return *this; 
	}

	Vector2d<T> operator / (Vector2d<T> const& other) const 
	{
		return Vector2d<T>(x / other.x, y / other.y); 
	}

	Vector2d<T>& operator /= (Vector2d<T> const& other)
	{
		x /= other.x; 
		y /= other.y; 
		return *this;
	}

	Vector2d<T> operator / (const T v) const 
	{
		return Vector2d<T>(x / v, y / v); 
	}

	Vector2d<T>& operator /= (const T v) 
	{
		x /= v; 
		y /= v; 
		return *this;
	}

	//! Get length of the vector.
	T length() const 
	{
		return math::sqrt( x*x + y*y ); 
	}

	//! Get squared length of the vector.
	T squareLength() const 
	{
		return x*x + y*y; 
	}
	
	//! Get distance from another point. 
	T getDistance(Vector2d<T> const& other) const
	{
		return Vector2d<T>(x - other.x, y - other.y).length();
	}

	//! Get squared distance from another point.
	T getSquaredDistance(Vector2d<T> const& other) const
	{
		return Vector2d<T>(x - other.x, y - other.y).squareLength();
	}

	//! Get the dot product of this vector with another
	T dot(Vector2d<T> const& other) const
	{
		return x*other.x + y*other.y;
	}
	
	//! Calculates angle of the vector
	T getAngle() const
	{
		T yaw = T(atan2( f64(x), f64(y) ));
		
		if (yaw <= -math::Pi) {
			yaw += math::DoublePi;
		} else if (yaw > math::Pi) {
			yaw -= math::DoublePi;
		}

		return math::RadToDeg(yaw);
	}

	//! Make the vector of unit length
	Vector2d<T>& normalize()
	{
		f32 length = squareLength();
		if ( length == 0 ) {
			return *this;
		}
		length = math::invSqrt(length);
		x = T(x * length);
		y = T(y * length);
		return *this;
	}

	//! Coordinate along X axis
	T x;
	//! Coordinate along Y axis
	T y;
};

// Initialization of static member
template<typename T>
Vector2d<T> const Vector2d<T>::zero = Vector2d(0);

//! Linear interpolation of two vectors
template<typename T>
Vector2d<T> lerp (Vector2d<T> const& v0, Vector2d<T> const& v1, f64 t)
{
	return (1.0-t)*v0 + t*v1;
}

} // namespace hrengin

#endif // _hrengin_Vector2d_
