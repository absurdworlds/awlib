/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Vector4d_
#define _aw_Vector4d_
#include <array>

#include <aw/math/math.h>

namespace aw {
//! Represents a 4-dimensional vector
template <class T>
class Vector<T,4> {
public:
	//! Default constructor. Constructs zero vector.
	Vector()
		: coord()
	{
	}

	//! Construct vector specifying individual coodrinates
	Vector(T const x, T const y, T const z, T const w)
		: coord({x,y,z,w})
	{
	}

	//! Construct vector with same value for coordinates
	explicit Vector(T const v)
		: coord({v,v,v,v})
	{
	}

	//! Copy constructor
	Vector(Vector<T,4> const& other) 
		: coord({other[0],other[1],other[2],other[3]})
	{
	}

	//! Set vector's components
	void set(T const x, T const y, T const z, T const w)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
		coord[3] = w;
	}

	void set(Vector<T,4> const& other)
	{
		coord[0] = other[0];
		coord[1] = other[1];
		coord[2] = other[2];
		coord[3] = other[3];
	}

	Vector<T,4>& operator = (Vector<T,4> const& other)
	{
		set(other);
		return *this;
	}

	Vector<T,4> operator + (Vector<T,4> const& other) const
	{
		return Vector<T,4>(
			coord[0] + other[0],
			coord[1] + other[1],
			coord[2] + other[2],
			coord[3] + other[3]);
	}

	//! Component-wise addition
	Vector<T,4>& operator += (Vector<T,4> const& other)
	{ 
		coord[0] += other[0];
		coord[1] += other[1];
		coord[2] += other[2];
		coord[3] += other[3];
		return *this;
	}

	Vector<T,4>& operator += (T const val)
	{
		coord[0] += val;
		coord[1] += val;
		coord[2] += val;
		coord[3] += val;
		return *this;
	}

	Vector<T,4>& operator -= (Vector<T,4> const& other)
	{
		coord[0] -= other[0];
		coord[1] -= other[1];
		coord[2] -= other[2];
		coord[3] -= other[3];
		return *this;
	}

	Vector<T,4>& operator -= (T const val)
	{
		coord[0] -= val;
		coord[1] -= val;
		coord[2] -= val;
		coord[3] -= val;
		return *this;
	}

	Vector<T,4>& operator *= (Vector<T,4> const& other)
	{
		coord[0] *= other[0];
		coord[1] *= other[1];
		coord[2] *= other[2];
		coord[3] *= other[3];
		return *this;
	}

	Vector<T,4>& operator *= (T const v)
	{
		coord[0] *= v;
		coord[1] *= v;
		coord[2] *= v;
		coord[3] *= v;
		return *this;
	}

	Vector<T,4>& operator /= (Vector<T,4> const& other)
	{
		coord[0] /= other[0];
		coord[1] /= other[1];
		coord[2] /= other[2];
		coord[3] /= other[3];
		return *this;
	}

	Vector<T,4>& operator /= (T const val)
	{
		T const inv = T(1.0/val);
		coord[0] *= inv; 
		coord[1] *= inv; 
		coord[2] *= inv; 
		coord[3] *= inv; 
		return *this; 
	}

	Vector<T,4> operator - () const
	{
		return Vector<T,4>(
			-coord[0],
			-coord[1],
			-coord[2],
			-coord[3]);
	}

	/*!
	 * Check if vectors are identical.
	 * \return
	 * 	`true` if vectors are identical, otherwise `false`.
	 */
	bool operator == (Vector<T,4> const& other) const
	{
		return (math::equals(coord[0], other[0]) &&
		        math::equals(coord[1], other[1]) &&
		        math::equals(coord[2], other[2]) &&
		        math::equals(coord[3], other[3]));
	}

	//! Calculate the dot product with another vector
	T dot(Vector<T,4> const& other) const
	{
		return coord[0]*other[0] +
		       coord[1]*other[1] +
		       coord[2]*other[2] +
		       coord[3]*other[3];
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

	//! Get distance from another point
	T distance(Vector<T,4> const& other) const
	{
		return (*this - other).length();
	}

	//! Get squared distance from another point
	T distanceSquared(Vector<T,4> const& other) const
	{
		return (*this - other).lengthSquared();
	}

	//! Set the length of the vector to a new value
	Vector<T,4>& setLength(T const newlength)
	{
		normalize();
		coord[0] *= newlength;
		coord[1] *= newlength;
		coord[2] *= newlength;
		coord[3] *= newlength;
		return *this;
	}

	//! Normalize the vector
	Vector<T,4>& normalize()
	{
		f64 length = lengthSquared();
		if (length == 0) {
			return *this;
		}

		length = math::invSqrt(length);

		coord[0] = T(coord[0] * length);
		coord[1] = T(coord[1] * length);
		coord[2] = T(coord[2] * length);
		coord[3] = T(coord[3] * length);

		return *this;
	}

	//! Get a normalized version of a vector without modifying it
	Vector<T,4> normalized() const
	{
		Vector<T,4> temp(*this);
		temp.normalize();

		return temp;
	}

	// Invert the vector.
	Vector<T,4>& invert()
	{
		coord[0] *= -1;
		coord[1] *= -1;
		coord[2] *= -1;
		coord[3] *= -1;
		return *this;
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = coord[0];
		array[1] = coord[1];
		array[2] = coord[2];
		array[3] = coord[3];
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

private:
	//! Coordinates of the vector
	std::array<T, 4> coord;
};

template<typename T>
using Vector4d = Vector<T,4>;

//! Partial specialization for integer vectors
//! Divide integer vector by scalar
template <>
inline Vector4d<i32>& Vector4d<i32>::operator /= (i32 const val) 
{
	coord[0] /= val;
	coord[1] /= val;
	coord[2] /= val;
	coord[3] /= val;
	return *this;
}

/*! Interpolate two vectors
	\param v0 The first vector to interpolate
	\param v1 The other vector to interpolate with.
	\param t The value to use to interpolate between v0 and v1
	Must be in range [0,1].
	\return Interpolated vector
 */
template<typename T>
Vector<T,4> lerp(Vector<T,4> const& v0, Vector<T,4> const& v1, f64 t)
{
	return (1.0 - t)*v0 + t*v1;
}

} // namespace aw
#endif//_aw_Vector4d_
