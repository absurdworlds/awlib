/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_Vector_h
#define aw_math_Vector_h
#include <array>
#include <tuple>
#include <utility>

#include <aw/math/math.h>
#include <aw/math/angle.h>
#include <aw/types/support/array.h>
#include <aw/types/traits/enable_if.h>
#include <aw/utility/index_sequence.h>

namespace aw {
template <typename T, size_t N>
struct Vector;

template<size_t I, typename T, size_t N>
T& get(Vector<T,N>& vec);

template<size_t I, typename T, size_t N>
T const& get(Vector<T,N> const& vec);


namespace Vec {
enum Coordinate {
	X, Y, Z, W
};
} // namespace Vec

template <typename T, size_t N>
struct Vector {
	static_assert(N > 0, "Vector must have non-zero number of dimensions");

	constexpr static size_t vector_size = N;

	using value_type = T;
	using array_type = std::array<T,N>;
	using tuple_type = decltype(aw::to_tuple(std::declval<array_type>()));

	value_type elems[N];

	/*
	template<typename...Args>
	Vector(Args... args)
		: elems{args...}
	{ }

	Vector(Vector<T,N> const& other)
		: elems(other.to_array())
	{ }

	//! Copy vector of same size
	template<typename U>
	Vector(Vector<U,N> const& other)
		: elems(convert_array<T>(other.to_array()))
	{ }*/

	//! Copy elements of other vector
	Vector<T,N>& operator = (Vector<T,N> const& other)
	{
		auto const& oth = other.elems;
		std::copy(std::begin(oth), std::end(oth), std::begin(elems));
		return *this;
	}

	Vector<T,N>& operator+=(Vector<T,N> const& other)
	{
		for_all([&] (size_t i) { elems[i] += other[i]; });
		return *this;
	}

	Vector<T,N>& operator-=(Vector<T,N> const& other)
	{
		for_all([&] (size_t i) { elems[i] -= other[i]; });
		return *this;
	}

	Vector<T,N>& operator*=(T const v)
	{
		for_all([&] (size_t i) { elems[i] *= v; });
		return *this;
	}

	Vector<T,N>& operator/=(T const v)
	{
		for_all([&] (size_t i) { elems[i] /= v; });
		return *this;
	}

	bool operator == (Vector<T,N> const& other) const
	{
		bool equal = true;
		for_all([&] (size_t i) {equal = equal && elems[i] == other[i];});
		return equal;
	}

	Vector<T,N>& negate()
	{
		return (*this *= -1);
	}

	friend T dot (Vector<T,N> const& vec1, Vector<T,N> const& vec2)
	{
		T product = {};
		for_all([&] (size_t i) { product += vec1[i] * vec2[i]; } );
		return product;
	}

	T lengthSq() const
	{
		return dot(*this,*this);
	}

	T length() const
	{
		return math::sqrt(lengthSq());
	}

	//! Normalize the vector
	Vector<T,N>& normalize()
	{
		T length = lengthSq();
		if (length == 0)
			return *this;

		length = math::invSqrt(length);

		return (*this *= length);
	}

	T& operator[](size_t idx)
	{
		return elems[idx];
	}

	T const& operator[](size_t idx) const
	{
		return elems[idx];
	}

	array_type to_array() const
	{
		return elems;
	}

	tuple_type to_tuple() const
	{
		return aw::to_tuple(elems);
	}

	template<typename Func>
	void for_each(Func func/*void(func)(T)*/)
	{
		for_all([&] (size_t i) { func(elems[i]); });
	}

	T& x()
	{
		return get<Vec::X>(*this);
	}

	T& y()
	{
		return get<Vec::Y>(*this);
	}

	T& z()
	{
		return get<Vec::Z>(*this);
	}

	T& w()
	{
		return get<Vec::W>(*this);
	}

	T x() const
	{
		return get<Vec::X>(*this);
	}

	T y() const
	{
		return get<Vec::Y>(*this);
	}

	T z() const
	{
		return get<Vec::Z>(*this);
	}

	T w() const
	{
		return get<Vec::W>(*this);
	}


private:
	constexpr static auto index = std::make_index_sequence<N>{};

	template <typename Func>
	static void for_all(Func func)
	{
		eval(func, index);
	}

	template <typename Func, size_t... I>
	static void eval(Func func, std::index_sequence<I...>)
	{
		int dummy[] = { (func(I), 0) ... };
	}
};

template<size_t I, typename T, size_t N>
T& get(Vector<T,N>& vec)
{
	static_assert(I < N, "Index out of bounds.");
	return vec[I];
}

template<size_t I, typename T, size_t N>
T const& get(Vector<T,N> const& vec)
{
	static_assert(I < N, "Index out of bounds.");
	return vec[I];
}

namespace detail {
template<size_t... Is, typename T, size_t N>
Vector<T,N-1> make_sub(Vector<T,N> const& vec, index_sequence<Is...>)
{
	return {get<Is>(vec)...};
}
} // namespace detail

template<size_t Index, typename T, size_t N>
Vector<T,N-1> sub(Vector<T,N> const& vec)
{
	auto range = index_cat<
	        make_index_range<0,Index>,
	        make_index_range<Index+1,N>
	>{};

	return detail::make_sub(vec, range);
}

//! Negate vector (reverse direction)
template<typename T, size_t N>
Vector<T,N> operator - (Vector<T,N> vec)
{
	return vec.negate();
}

//! Identity
template<typename T, size_t N>
Vector<T,N> operator + (Vector<T,N> vec)
{
	return vec;
}

//! Sum of two vectors
template<typename T, size_t N>
Vector<T,N> operator + (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 += v2;
	return v1;
}

//! Difference of two vectors
template<typename T, size_t N>
Vector<T,N> operator - (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 -= v2;
	return v1;
}

//! Scalar-vector product
template<typename T, size_t N, typename Scalar>
Vector<T,N> operator * (Vector<T,N> vec, Scalar const v)
{
	vec *= v;
	return vec;
}

//! Scalar-vector product
template<typename T, size_t N, typename Scalar>
Vector<T,N> operator / (Vector<T,N> vec, Scalar const v)
{
	vec /= v;
	return vec;
}

//! Scalar-vector product
template<typename T, size_t N, typename Scalar>
Vector<T,N> operator * (Scalar const v, Vector<T,N> vec)
{
	vec *= v;
	return vec;
}

//! Get a normalized version of a vector
template<typename T, size_t N>
Vector<T,N> normalize(Vector<T,N> vec)
{
	return vec.normalize();
}

//! Get distance between two points
template<typename T, size_t N>
T distance(Vector<T,N> vec1, Vector<T,N> const& vec2)
{
	return (vec1 - vec2).length();
}

//! Get squared distance between two points
template<typename T, size_t N>
T distanceSq(Vector<T,N> vec1, Vector<T,N> const& vec2)
{
	return (vec1 - vec2).lengthSq();
}

template<typename T, size_t N>
void fill(Vector<T,N>& vec, T const value)
{
	std::fill(std::begin(vec.elems), std::end(vec.elems), value);
}
} // namespace aw
#endif//aw_math_Vector_h
