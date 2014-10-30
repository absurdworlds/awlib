/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Vector4d_
#define _hrengin_Vector4d_

#include <hrengin/common/compiler_setup.h>

#ifdef HR_COMPILER_MSC // fucking microsoft
#include <array>
#endif

#include <hrengin/math/math.h>


namespace hrengin {

//! Represents a 4-dimensional vector
template <class T>
class Vector4d {
public:
	//! Default constructor. Constructs zero vector.
	Vector4d ()
#ifndef HR_COMPILER_MSC // fucking microsoft
		: coord_{}
#else
		: coord_()
#endif
	{
	}

	//! Construct vector specifying individual coodrinates
	Vector4d (T const x, T const y, T const z, T const w)
#ifndef HR_COMPILER_MSC // fucking microsoft
		: coord_{x,y,z,w}
#else
		: coord_({x,y,z,w})
#endif
	{
	}

	//! Construct vector with same value for coordinates
	explicit Vector4d (T const v)
#ifndef HR_COMPILER_MSC // fucking microsoft
		: coord_{v,v,v,v}
#else
		: coord_{v,v,v,v}
#endif
	{
	}

	//! Copy constructor
	Vector4d(Vector4d<T> const& other) 
#ifndef HR_COMPILER_MSC // fucking microsoft
		: coord_{other[0],other[1],other[2],other[3]}
#else
		: coord_({other[0],other[1],other[2],other[3]})
#endif
	{
	}

	//! Set vector's components
	void set (T const x, T const y, T const z, T const w)
	{
		coord_[0] = x;
		coord_[1] = y;
		coord_[2] = z;
		coord_[3] = w;
	}

	void set (Vector4d<T> const& other)
	{
		coord_[0] = other[0];
		coord_[1] = other[1];
		coord_[2] = other[2];
		coord_[3] = other[3];
	}
	
	Vector4d<T>& operator = (Vector4d<T> const& other)
	{
		set(other);
		return *this;
	}
	
	Vector4d<T> operator + (Vector4d<T> const& other) const
	{
		return Vector4d<T>(
			coord_[0] + other[0],
			coord_[1] + other[1],
			coord_[2] + other[2],
			coord_[3] + other[3]);
	}

	//! Component-wise addition
	Vector4d<T>& operator += (Vector4d<T> const& other)
	{ 
		coord_[0] += other[0];
		coord_[1] += other[1];
		coord_[2] += other[2];
		coord_[3] += other[3];
		return *this;
	}

	Vector4d<T> operator + (T const val) const
	{
		return Vector4d<T>(
			coord_[0] + val,
			coord_[1] + val,
			coord_[2] + val,
			coord_[3] + val);
	}

	Vector4d<T>& operator += (T const val)
	{
		coord_[0] += val;
		coord_[1] += val;
		coord_[2] += val;
		coord_[3] += val;
		return *this;
	}

	Vector4d<T> operator - (Vector4d<T> const& other) const
	{
		return Vector4d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1],
			coord_[2] - other[2],
			coord_[3] - other[3]);
	}

	Vector4d<T>& operator -= (Vector4d<T> const& other)
	{
		coord_[0] -= other[0];
		coord_[1] -= other[1];
		coord_[2] -= other[2];
		coord_[3] -= other[3];
		return *this;
	}

	Vector4d<T> operator - (T const val) const
	{
		return Vector4d<T>(
			coord_[0] - val,
			coord_[1] - val,
			coord_[2] - val,
			coord_[3] - val);
	}

	Vector4d<T>& operator -= (T const val)
	{
		coord_[0] -= val;
		coord_[1] -= val;
		coord_[2] -= val;
		coord_[3] -= val;
		return *this;
	}

	Vector4d<T> operator * (Vector4d<T> const& other) const
	{
		return Vector4d<T>(
			coord_[0] * other[0],
			coord_[1] * other[1],
			coord_[2] * other[2],
			coord_[3] * other[3]);
	}

	Vector4d<T>& operator *= (Vector4d<T> const& other)
	{
		coord_[0] *= other[0];
		coord_[1] *= other[1];
		coord_[2] *= other[2];
		coord_[3] *= other[3];
		return *this;
	}

	Vector4d<T> operator * (T const v) const
	{
		return Vector4d<T>(
			coord_[0] * v,
			coord_[1] * v,
			coord_[2] * v,
			coord_[3] * v);
	}

	Vector4d<T>& operator *= (T const v)
	{
		coord_[0] *= v;
		coord_[1] *= v;
		coord_[2] *= v;
		coord_[3] *= v;
		return *this;
	}

	Vector4d<T> operator / (Vector4d<T> const& other) const
	{
		return Vector4d<T>(
			coord_[0] / other[0],
			coord_[1] / other[1],
			coord_[2] / other[2],
			coord_[3] / other[3]);
	}

	Vector4d<T>& operator /= (Vector4d<T> const& other)
	{
		coord_[0] /= other[0];
		coord_[1] /= other[1];
		coord_[2] /= other[2];
		coord_[3] /= other[3];
		return *this;
	}

	Vector4d<T> operator / (T const val) const
	{
		T inv = T(1.0/val);
		return Vector4d<T>(
			coord_[0] * inv,
			coord_[1] * inv,
			coord_[2] * inv,
			coord_[3] * inv);
	}

	Vector4d<T>& operator /= (T const val)
	{
		T const inv = T(1.0/val);
		coord_[0] *= inv; 
		coord_[1] *= inv; 
		coord_[2] *= inv; 
		coord_[3] *= inv; 
		return *this; 
	}
	

	Vector4d<T> operator - () const
	{
		return Vector4d<T>(
			-coord_[0],
			-coord_[1],
			-coord_[2],
			-coord_[3]);
	}

	
	//! Normalize the vector
	Vector4d<T>& normalize()
	{
		f64 length = squareLength();
		if (length == 0) {
			return *this;
		}

		length = math::invSqrt(length);

		coord_[0] = T(coord_[0] * length);
		coord_[1] = T(coord_[1] * length);
		coord_[2] = T(coord_[2] * length);
		coord_[3] = T(coord_[3] * length);

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

		return Vector4d<T>(
			T(coord_[0] * length),
			T(coord_[1] * length),
			T(coord_[2] * length),
			T(coord_[3] * length));
	}

	//! Get length of the vector.
	T length() const
	{ 
		return math::sqrt(
			coord_[0]*coord_[0] +
			coord_[1]*coord_[1] +
			coord_[2]*coord_[2] +
			coord_[3]*coord_[3] );
	}
	
	//! Get squared length of the vector.
	T squareLength() const
	{ 
		return  coord_[0]*coord_[0] +
			coord_[1]*coord_[1] +
			coord_[2]*coord_[2] +
			coord_[3]*coord_[3];
	}

	//! Calculate the dot product with another vector
	T dot(Vector4d<T> const& other) const
	{
		return  coord_[0]*other[0] +
			coord_[1]*other[1] +
			coord_[2]*other[2] +
			coord_[3]*other[3];
	}

	//! Get distance from another point
	T getDistance(Vector4d<T> const& other) const
	{
		return Vector4d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1],
			coord_[2] - other[2],
			coord_[3] - other[3]).length();
	}

	//! Get squared distance from another point
	T getDistanceSQ(Vector4d<T> const& other) const
	{
		return Vector4d<T>(
			coord_[0] - other[0],
			coord_[1] - other[1],
			coord_[2] - other[2],
			coord_[3] - other[3]).squareLength();
	}

	//! Set the length of the vector to a new value
	Vector4d<T>& setLength(T const newlength)
	{
		normalize();
		coord_[0] *= newlength;
		coord_[1] *= newlength;
		coord_[2] *= newlength;
		coord_[3] *= newlength;
		return *this;
	}
	
	// Invert the vector.
	Vector4d<T>& invert ()
	{
		coord_[0] *= -1;
		coord_[1] *= -1;
		coord_[2] *= -1;
		coord_[3] *= -1;
		return *this;
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = coord_[0];
		array[1] = coord_[1];
		array[2] = coord_[2];
		array[3] = coord_[3];
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

private:
#ifndef HR_COMPILER_MSC // fucking microsoft
	//! Coordinates of the vector
	T coord_[4];
#else
	//! Coordinates of the vector
	std::array<T, 4> coord_;
#endif
};

//! Partial specialization for integer vectors
//! Divide integer vector by scalar
template <>
inline Vector4d<i32> Vector4d<i32>::operator / (i32 const val) const 
{
	return Vector4d<i32>(
		coord_[0]/val,
		coord_[1]/val,
		coord_[2]/val,
		coord_[3]/val);
}

//! Partial specialization for integer vectors
//! Divide integer vector by scalar
template <>
inline Vector4d<i32>& Vector4d<i32>::operator /= (i32 const val) 
{
	coord_[0] /= val;
	coord_[1] /= val;
	coord_[2] /= val;
	coord_[3] /= val;
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
