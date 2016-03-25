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
#include <aw/types/traits/enable_if.h>

namespace aw {
namespace detail {
template<typename T, size_t... I>
std::array<T,sizeof...(I)+1>
extend_array(std::array<T,sizeof...(I)>&& array, std::index_sequence<I...>)
{
	return {array[I]..., 0};
}

template<typename L, typename T, size_t... I>
std::array<L,sizeof...(I)>
convert_array(std::array<T,sizeof...(I)>&& array, std::index_sequence<I...>)
{
	return {array[I]...};
}
} // namespace detail

template<typename T, size_t N>
std::array<T,N+1> extend_array(std::array<T,N>&& array)
{
	auto index = std::make_index_sequence<N>{};
	return detail::extend_array(std::forward<std::array<T,N>>(array), index);
}

template<typename L, typename T, size_t N>
std::array<L,N> convert_array(std::array<T,N>&& array)
{
	auto index = std::make_index_sequence<N>{};
	return detail::convert_array<L>(std::forward<std::array<T,N>>(array), index);
}

namespace Vec {
enum Coordinate {
	X, Y, Z, W
};
}

template <typename T, size_t N>
struct Vector {
	static_assert(N >= 2, "Vector must have 2 or more dimensions");

	constexpr static size_t vector_size = N;

	using value_type = T;
	using base_type = std::array<T,N>;

	//! Default constructor. Constructs zero vector.
	Vector()
		: elems()
	{ }

	//! Construct vector with same value for elemsinates
	explicit Vector(T const v)
	{
		elems.fill(v);
	}

	explicit Vector(Vector<T,N-1> const& vec)
		: elems(extend_array(vec.to_array()))
	{
	}

	//! Construct vector with individual coodrinates
	template<typename...Args>
	Vector(Args const... args)
		: elems{args...}
	{
	}

	//! Copy array of same size
	template<typename U>
	Vector(Vector<U,N> const& other)
		: elems(convert_array<T>(other.to_array()))
	{
	}

	//! Set elements of the vector
	template<typename...Args>
	void set(Args const... args)
	{
		elems = {args...};
	}

	//! Copy elemsinates of other vector
	void set(Vector<T,N> const& other)
	{
		elems = other.elems;
	}

	//! Copy elemsinates of other vector
	Vector<T,N>& operator = (Vector<T,N> const& other)
	{
		set(other);
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
		T inv = 1 / v;
		for_all([&] (size_t i) { elems[i] *= inv; });
		return *this;
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

	template<size_t I>
	T& get()
	{
		static_assert(I < vector_size, "Index out of bounds.");
		return elems[I];
	}

	template<size_t I>
	T const& get() const
	{
		static_assert(I < vector_size, "Index out of bounds.");
		return elems[I];
	}

	T& operator[](size_t index)
	{
		return elems[index];
	}

	T const& operator[](size_t index) const
	{
		return elems[index];
	}

	std::array<T,vector_size> to_array() const
	{
		return elems;
	}
	
	auto to_tuple() const
	{
		auto index = std::make_index_sequence<N>{};
		to_tuple(index);
	}

	template<typename Func>
	void for_each(Func func/*void(func)(T)*/)
	{
		for_all([&] (size_t i) { func(elems[i]); });
	}

	T& x()
	{
		static_assert(N <= 4, "No such method!");
		return get<Vec::X>();
	}

	T& y()
	{
		static_assert(N <= 4, "No such method!");
		return get<Vec::Y>();
	}

	T& z()
	{
		static_assert(N >= 3 && N <= 4, "No such method!");
		return get<Vec::Z>();
	}

	T& w()
	{
		static_assert(N == 4, "No such method!");
		return get<Vec::W>();
	}

	T x() const
	{
		static_assert(N <= 4, "No such method!");
		return get<Vec::X>();
	}

	T y() const
	{
		static_assert(N <= 4, "No such method!");
		return get<Vec::Y>();
	}

	T z() const
	{
		static_assert(N >= 3 && N <= 4, "No such method!");
		return get<Vec::Z>();
	}

	T w() const
	{
		static_assert(N == 4, "No such method!");
		return get<Vec::W>();
	}

private:
	base_type elems;

	template <size_t... I>
	auto to_tuple(std::index_sequence<I...>)
	{
		return std::make_tuple(elems[I]...);
	}

	template <typename Func>
	static void for_all(Func func)
	{
		auto index = std::make_index_sequence<N>{};
		eval(func, index);
	}

	template <typename Func, size_t... I>
	static void eval(Func func, std::index_sequence<I...>)
	{
		int dummy[] = { (func(I), 0) ... };
	}
};

//! Negate vector (reverse direction)
Vector<T,N> operator - (Vector<T,N> vec)
{
	return vec.negate();
}

//! Identity
Vector<T,N> operator + (Vector<T,N> vec)
{
	return vec;
}

//! Sum of two vectors
Vector<T,N> operator + (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 += v2;
	return v1;
}

//! Difference of two vectors
Vector<T,N> operator - (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 -= v2;
	return v1;
}

//! Scalar-vector product
template<typename Scalar>
Vector<T,N> operator * (Vector<T,N> vec, Scalar const v)
{
	vec *= v;
	return vec;
}

//! Scalar-vector product
template<typename Scalar>
Vector<T,N> operator / (Vector<T,N> vec, Scalar const v)
{
	vec /= v;
	return vec;
}

//! Scalar-vector product
template<typename Scalar>
Vector<T,N> operator * (Scalar const v, Vector<T,N> vec)
{
	vec *= v;
	return vec;
}

//! Get a normalized version of a vector
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


} // namespace aw
#endif//aw_math_Vector_h
