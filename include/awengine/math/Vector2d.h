/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Vector2d_
#define _awrts_Vector2d_
#include <array>

#include <awengine/math/math.h>

namespace awrts {
//! Represents positions and directions in 2D space
template <typename T>
class Vector2d {
public:
	//! Default constructor. Constructs zero vector.
	Vector2d()
		: coord_()
	{
	}

	//! Construct vector with same both coordinates 
	explicit Vector2d(T v)
		: coord_({v, v})
	{
	}

	//! Construct vector with individual coodrinates
	Vector2d(T x, T y)
		: coord_({x, y})
	{
	}


	//! Copy constructor
	Vector2d(Vector2d<T> const& other)
		: coord_({other[0], other[1]})
	{
	}

	//! Predefined instance of zero vector
	static Vector2d<T> const zero;

	Vector2d<T>& operator = (Vector2d<T> const& other)
	{
		coord_[0] = other[0];
		coord_[1] = other[1];
		return *this;
	}

	Vector2d<T> operator - () const
	{
		return Vector2d<T>(
			-coord_[0],
			-coord_[1]);
	}

	Vector2d<T> operator + (Vector2d<T> const& other) const
	{
		return Vector2d<T>(coord_[0] + other[0], coord_[1] + other[1]);
	}

	Vector2d<T>& operator += (Vector2d<T> const& other)
	{
		coord_[0] += other[0];
		coord_[1] += other[1];
		return *this;
	}

	Vector2d<T> operator + (T const v) const
	{
		return Vector2d<T>(coord_[0] + v, coord_[1] + v);
	}

	Vector2d<T>& operator += (T const v)
	{
		coord_[0] += v;
		coord_[1] += v;
		return *this;
	}

	Vector2d<T> operator - (Vector2d<T> const& other) const
	{ 
		return Vector2d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1]);
	}

	Vector2d<T>& operator -= (Vector2d<T> const& other)
	{ 
		coord_[0] -= other[0];
		coord_[1] -= other[1];
		return *this;
	}

	Vector2d<T> operator - (T const v) const
	{ 
		return Vector2d<T>(
			coord_[0] - v,
			coord_[1] - v);
	}

	Vector2d<T>& operator -= (T const v)
	{ 
		coord_[0] -= v;
		coord_[1] -= v;
		return *this;
	}

	Vector2d<T> operator * (Vector2d<T> const& other) const
	{ 
		return Vector2d<T>(
			coord_[0] * other[0],
			coord_[1] * other[1]);
	}

	Vector2d<T>& operator *= (Vector2d<T> const& other)
	{ 
		coord_[0] *= other[0];
		coord_[1] *= other[1];
		return *this;
	}

	Vector2d<T> operator * (T const v) const
	{ 
		return Vector2d<T>(
			coord_[0] * v,
			coord_[1] * v);
	}

	Vector2d<T>& operator *= (T const v)
	{
		coord_[0] *= v;
		coord_[1] *= v;
		return *this;
	}

	Vector2d<T> operator / (Vector2d<T> const& other) const
	{
		return Vector2d<T>(
			coord_[0] / other[0],
			coord_[1] / other[1]);
	}

	Vector2d<T>& operator /= (Vector2d<T> const& other)
	{
		coord_[0] /= other[0];
		coord_[1] /= other[1];
		return *this;
	}

	Vector2d<T> operator / (const T v) const
	{
		return Vector2d<T>(
			coord_[0] / v,
			coord_[1] / v);
	}

	Vector2d<T>& operator /= (const T v)
	{
		coord_[0] /= v;
		coord_[1] /= v;
		return *this;
	}

	//! Get length of the vector.
	T length() const
	{
		return math::sqrt(coord_[0]*coord_[0] +
				  coord_[1]*coord_[1]);
	}

	//! Get squared length of the vector.
	T squareLength() const
	{
		return  coord_[0]*coord_[0] +
			coord_[1]*coord_[1];
	}

	//! Get distance from another point.
	T getDistance(Vector2d<T> const& other) const
	{
		return Vector2d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1]).length();
	}

	//! Get squared distance from another point.
	T getSquaredDistance(Vector2d<T> const& other) const
	{
		return Vector2d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1]).squareLength();
	}

	//! Get the dot product of this vector with another
	T dot(Vector2d<T> const& other) const
	{
		return coord_[0]*other[0] + coord_[1]*other[1];
	}

	//! Calculates angle of the vector
	T getAngle() const
	{
		T yaw = T(atan2( f64(coord_[0]), f64(coord_[1]) ));

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
		coord_[0] = T(coord_[0] * length);
		coord_[1] = T(coord_[1] * length);
		return *this;
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

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = coord_[0];
		array[1] = coord_[1];
		array[2] = 0;
		array[3] = 0;
	}

	//! Fill an array of 3 values with the vector data
	void toArrayOf3(T* array) const
	{
		array[0] = coord_[0];
		array[1] = coord_[1];
		array[2] = 0;
	}

	//! Fill an array of 2 values with the vector data
	void toArrayOf2(T* array) const
	{
		array[0] = coord_[0];
		array[1] = coord_[1];
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
private:
	//! Coordinates of the vector
	std::array<T, 2> coord_;
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

} // namespace awrts
#endif // _awrts_Vector2d_
