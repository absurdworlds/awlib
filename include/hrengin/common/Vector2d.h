/**
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

/*
	Self-explanatory, a template class for defining 2D positions and
	directions
 */
template <typename T>
class Vector2d {
public:
	T X;
	T Y;

public:
	Vector2d() 
		: X(0), Y(0) 
	{
	}

	Vector2d(T x, T y) 
		: X(x), Y(y) 
	{
	}
	
	/*
	   Initialize both coordinates with same value
	   It is defined as explicit to avoid accidental mistakes
	 */
	explicit Vector2d(T v) 
		: X(v), Y(v) 
	{
	}

	Vector2d(const Vector2d<T>& other) 
		: X(other.X), Y(other.Y)
	{
	}

	Vector2d<T>& operator = (const Vector2d<T>& other)
	{
		X = other.X; 
		Y = other.Y; 
		return *this; 
	}

	Vector2d<T> operator - () const 
	{
		return Vector2d<T>(-X, -Y);
	}

	
	Vector2d<T> operator + (const Vector2d<T>& other) const 
	{
		return Vector2d<T>(X + other.X, Y + other.Y);
	}

	Vector2d<T>& operator += (const Vector2d<T>& other) 
	{
		X+=other.X; 
		Y+=other.Y; 
		return *this; 
	}

	Vector2d<T> operator - (const Vector2d<T>& other) const 
	{ 
		return Vector2d<T>(X - other.X, Y - other.Y); 
	}

	Vector2d<T>& operator -= (const Vector2d<T>& other) 
	{ 
		X-=other.X; 
		Y-=other.Y; 
		return *this; 
	}

	Vector2d<T> operator - (const T v) const 
	{ 
		return Vector2d<T>(X - v, Y - v); 
	}

	Vector2d<T>& operator -= (const T v) 
	{ 
		X-=v; 
		Y-=v; 
		return *this; 
	}

	Vector2d<T> operator * (const Vector2d<T>& other) const 
	{ 
		return Vector2d<T>(X * other.X, Y * other.Y); 
	}

	Vector2d<T>& operator *= (const Vector2d<T>& other) 
	{ 
		X*=other.X; 
		Y*=other.Y; 
		return *this; 
	}

	Vector2d<T> operator * (const T v) const
	{ 
		return Vector2d<T>(X * v, Y * v);
	}

	Vector2d<T>& operator *= (const T v) 
	{
		X*=v; 
		Y*=v; 
		return *this; 
	}

	Vector2d<T> operator / (const Vector2d<T>& other) const 
	{
		return Vector2d<T>(X / other.X, Y / other.Y); 
	}

	Vector2d<T>& operator /= (const Vector2d<T>& other)
	{
		X/=other.X; 
		Y/=other.Y; 
		return *this;
	}

	Vector2d<T> operator / (const T v) const 
	{
		return Vector2d<T>(X / v, Y / v); 
	}

	Vector2d<T>& operator /= (const T v) 
	{
		X/=v; 
		Y/=v; 
		return *this;
	}
	
	/* Functions */

	// Get length of the vector.
	T length() const 
	{
		return math::sqrt( X*X + Y*Y ); 
	}

	// Get squared length of the vector.
	T squareLength() const 
	{
		return X*X + Y*Y; 
	}
	
	// Gets distance from another point. 
	T getDistance(const Vector2d<T>& other) const
	{
		return Vector2d<T>(X - other.X, Y - other.Y).length();
	}

	// Get squared distance from another point.
	T getSquaredDistance(const Vector2d<T>& other) const
	{
		return Vector2d<T>(X - other.X, Y - other.Y).squareLength();
	}

	// Get the dot product of this vector with another
	T dot(const Vector2d<T>& other) const
	{
		return X*other.X + Y*other.Y;
	}
	
	// Normalize the vector
	vector2d<T>& normalize()
	{
		f32 length = squareLength();
		if ( length == 0 ) {
			return *this;
		}
		length = math::invSqrt(length);
		X = (T)(X * length);
		Y = (T)(Y * length);
		return *this;
	}
	
	Vector2d<T> lerp (const Vector2d<T>& other, f64 t) const
	{
		const f64 inv = 1.0 - d;
		return Vector2d<T>(T(X*inv + other.X*d), T(Y*inv + other.Y*d));
	}

};

} // namespace hrengin

#endif // _hrengin_Vector2d_
