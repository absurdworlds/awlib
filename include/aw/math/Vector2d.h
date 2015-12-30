/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Vector2d_
#define _aw_Vector2d_
#include <aw/math/Vector.h>

namespace aw {
//! Represents positions and directions in 2D space
template <typename T>
class Vector<T,2> {
public:
	//! Default constructor. Constructs zero vector.
	Vector()
		: coord()
	{
	}

	//! Construct vector with same both coordinates 
	explicit Vector(T v)
		: coord({v, v})
	{
	}

	//! Construct vector with individual coodrinates
	Vector(T x, T y)
		: coord({x, y})
	{
	}

	//! Copy constructor
	Vector(Vector<T,2> const& other)
		: coord({other[0], other[1]})
	{
	}

	Vector<T,2>& operator = (Vector<T,2> const& other)
	{
		coord[0] = other[0];
		coord[1] = other[1];
		return *this;
	}

	Vector<T,2>& operator += (Vector<T,2> const& other)
	{
		coord[0] += other[0];
		coord[1] += other[1];
		return *this;
	}

	Vector<T,2>& operator += (T const v)
	{
		coord[0] += v;
		coord[1] += v;
		return *this;
	}

	Vector<T,2>& operator -= (Vector<T,2> const& other)
	{ 
		coord[0] -= other[0];
		coord[1] -= other[1];
		return *this;
	}

	Vector<T,2>& operator -= (T const v)
	{ 
		coord[0] -= v;
		coord[1] -= v;
		return *this;
	}

	Vector<T,2>& operator *= (Vector<T,2> const& other)
	{ 
		coord[0] *= other[0];
		coord[1] *= other[1];
		return *this;
	}

	Vector<T,2>& operator *= (T const v)
	{
		coord[0] *= v;
		coord[1] *= v;
		return *this;
	}

	Vector<T,2>& operator /= (Vector<T,2> const& other)
	{
		coord[0] /= other[0];
		coord[1] /= other[1];
		return *this;
	}

	Vector<T,2>& operator /= (const T v)
	{
		coord[0] /= v;
		coord[1] /= v;
		return *this;
	}

	Vector<T,2>& invert()
	{
		return (*this *= -1);
	}

	//! Get the dot product of this vector with another
	T dot(Vector<T,2> const& other) const
	{
		return coord[0]*other[0] + coord[1]*other[1];
	}

	//! Get squared length of the vector.
	T lengthSquared() const
	{
		return dot(this);
	}

	//! Get length of the vector.
	T length() const
	{
		return math::sqrt(lengthSquared());
	}

	//! Get distance from another point.
	T distance(Vector<T,2> const& other) const
	{
		return (*this - other).length();
	}

	//! Get squared distance from another point.
	T distanceSquared(Vector<T,2> const& other) const
	{
		return (*this - other).lengthSquared();
	}

	//! Calculates angle of the vector
	T angle() const
	{
		T yaw = T(atan2(f64(coord[0]), f64(coord[1])));

		if (yaw <= -math::Pi) {
			yaw += math::DoublePi;
		} else if (yaw > math::Pi) {
			yaw -= math::DoublePi;
		}

		return math::radToDeg(yaw);
	}

	//! Make the vector of unit length
	Vector<T,2>& normalize()
	{
		f32 length = lengthSquared();
		if (length == 0)
			return *this;

		length = math::invSqrt(length);
		
		this *= length;

		return *this;
	}


	//! Access elements of the vector by subscript
	T& operator [] (size_t elem)
	{
		return coord[elem];
	}

	//! Access elements of the vector by subscript
	T const& operator [] (size_t elem) const
	{
		return coord[elem];
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = coord[0];
		array[1] = coord[1];
		array[2] = 0;
		array[3] = 0;
	}

	//! Fill an array of 3 values with the vector data
	void toArrayOf3(T* array) const
	{
		array[0] = coord[0];
		array[1] = coord[1];
		array[2] = 0;
	}

	//! Fill an array of 2 values with the vector data
	void toArrayOf2(T* array) const
	{
		array[0] = coord[0];
		array[1] = coord[1];
	}

	//! Get coordinate along X axis
	T& x()
	{
		return coord[0];
	}

	//! Get coordinate along Y axis
	T& y()
	{
		return coord[1];
	}

	//! Get coordinate along X axis
	T const& x() const
	{
		return coord[0];
	}

	//! Get coordinate along Y axis
	T const& y() const
	{
		return coord[1];
	}
	
private:
	//! Coordinates of the vector
	std::array<T,2> coord;
};

template<typename T>
using Vector2d = Vector<T,2>;
} // namespace aw
#endif // _aw_Vector2d_
