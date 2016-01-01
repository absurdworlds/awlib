/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_Vector_h
#define aw_math_Vector_h
#include <array>

#include <aw/math/math.h>
#include <aw/math/angle.h>

namespace aw {
//! Represents positions and directions
template <typename T, size_t N>
class Vector {
};

template<typename T, size_t N>
Vector<T,N> operator - (Vector<T,N> vec)
{
	vec.invert();
	return vec;
}

template<typename T, size_t N>
Vector<T,N> operator + (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 += v2;
	return v1;
}

template<typename T, size_t N>
Vector<T,N> operator - (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 -= v2;
	return v1;
}

template<typename T, size_t N>
Vector<T,N> operator * (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 *= v2;
	return v1;
}

template<typename T, size_t N>
Vector<T,N> operator / (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 /= v2;
	return v1;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator + (Vector<T,N> vec, Scalar const v)
{
	vec += v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator - (Vector<T,N> vec, Scalar const v)
{
	vec -= v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator * (Vector<T,N> vec, Scalar const v)
{
	vec *= v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator / (Vector<T,N> vec, Scalar const v)
{
	vec /= v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator + (Scalar const v, Vector<T,N> vec)
{
	vec += v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator - (Scalar const v, Vector<T,N> vec)
{
	vec -= v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator * (Scalar const v, Vector<T,N> vec)
{
	vec *= v;
	return vec;
}

template<typename T, size_t N, typename Scalar>
Vector<T,N> operator / (Scalar const v, Vector<T,N> vec)
{
	vec /= v;
	return vec;
}
} // namespace aw
#endif//aw_math_Vector_h
