/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_vector_h
#define aw_math_vector_h
#include <utility>

#include <aw/math/math.h>
#include <aw/math/angle.h>
#include <aw/meta/conditional.h>
#include <aw/utility/index_sequence.h>
#include <aw/meta/list_ops.h>

namespace aw {
namespace math {
template <typename T, size_t N>
struct vector;

template<size_t I, typename T, size_t N>
constexpr T& get(vector<T,N>& vec);

template<size_t I, typename T, size_t N>
constexpr T const& get(vector<T,N> const& vec);


namespace axis {
constexpr size_t x = 0;
constexpr size_t y = 1;
constexpr size_t z = 2;
constexpr size_t w = 3;
} // namespace axis

template <class VectorT, class = typename VectorT::indices>
struct vector_ops;

template <class T, size_t N, size_t...Is>
struct vector_ops<vector<T,N>,index_sequence<Is...>>
{
	using VectorT = vector<T,N>;

	static constexpr void set(VectorT& vec, VectorT const& other)
	{
		(void(vec[Is] = other[Is]), ...);
	}

	static constexpr void add(VectorT& vec, VectorT const& other)
	{
		(void(vec[Is] += other[Is]), ...);
	}

	static constexpr void sub(VectorT& vec, VectorT const& other)
	{
		(void(vec[Is] -= other[Is]), ...);
	}

	static constexpr void mul(VectorT& vec, T const& val)
	{
		(void(vec[Is] *= val), ...);
	}

	static constexpr void div(VectorT& vec, T const& val)
	{
		(void(vec[Is] /= val), ...);
	}

	static constexpr T dot(VectorT const& vec1, VectorT const& vec2)
	{
		// FIXME: T{} workaround for GCC 6.1 bug
		T product = (T{vec1[Is]*vec2[Is]} + ...);
		return product;
	}

	template<typename Func>
	static constexpr void for_each(VectorT& vec, Func func)
	{
		(func(vec[Is]), ...);
	}

	template<typename Func>
	static constexpr VectorT make(VectorT const& vec, Func func)
	{
		return { func(vec[Is]) ... };
	}

	template<typename Func>
	static constexpr void apply(VectorT& vec, Func func)
	{
		set(vec, make(vec, func));
	}
};

template <typename T, size_t N>
struct vector {
	static_assert(N > 0, "Vector must have non-zero number of dimensions");

	constexpr static size_t vector_size = N;

	using value_type = T;

	using indices = std::make_index_sequence<N>;

	value_type elems[N];

	constexpr vector& operator=(vector const& other)
	{
		vector_ops<vector>::set(*this, other);
		return *this;
	}

	constexpr vector& operator+=(vector const& other)
	{
		vector_ops<vector>::add(*this, other);
		return *this;
	}

	constexpr vector& operator-=(vector const& other)
	{
		vector_ops<vector>::sub(*this, other);
		return *this;
	}

	constexpr vector& operator*=(T const v)
	{
		vector_ops<vector>::mul(*this, v);
		return *this;
	}

	constexpr vector& operator/=(T const v)
	{
		vector_ops<vector>::div(*this, v);
		return *this;
	}

	constexpr vector& negate()
	{
		return (*this *= -1);
	}

	constexpr T dot(vector const& other) const
	{
		return vector_ops<vector>::dot(*this, other);
	}

	constexpr T length_sq() const
	{
		return dot(*this);
	}

	T length() const
	{
		return math::sqrt(length_sq());
	}

	//! Normalize the vector
	vector& normalize()
	{
		T length = length_sq();
		if (length == 0)
			return *this;

		length = math::invSqrt(length);

		return (*this *= length);
	}

	constexpr T& operator[](size_t idx)
	{
		return elems[idx];
	}

	constexpr T const& operator[](size_t idx) const
	{
		return elems[idx];
	}

	template<typename Func>
	constexpr vector& for_each(Func func)
	{
		vector_ops<vector>::for_each(*this, func);
		return *this;
	}

	template<typename Func>
	constexpr vector& apply(Func func)
	{
		vector_ops<vector>::apply(*this, func);
		return *this;
	}

	constexpr T& x()
	{
		return get<axis::x>(*this);
	}

	constexpr T& y()
	{
		return get<axis::y>(*this);
	}

	constexpr T& z()
	{
		return get<axis::z>(*this);
	}

	constexpr T& w()
	{
		return get<axis::w>(*this);
	}

	constexpr T const& x() const
	{
		return get<axis::x>(*this);
	}

	constexpr T const& y() const
	{
		return get<axis::y>(*this);
	}

	constexpr T const& z() const
	{
		return get<axis::z>(*this);
	}

	constexpr T const& w() const
	{
		return get<axis::w>(*this);
	}
};

template<typename T, size_t N>
constexpr T dot(vector<T,N> const& vec1, vector<T,N> const& vec2)
{
	return vec1.dot(vec2);
}

template<size_t I, typename T, size_t N>
constexpr T& get(vector<T,N>& vec)
{
	static_assert(I < N, "Index out of bounds.");
	return vec[I];
}

template<size_t I, typename T, size_t N>
constexpr T const& get(vector<T,N> const& vec)
{
	static_assert(I < N, "Index out of bounds.");
	return vec[I];
}

namespace _impl {
template<size_t... Is, typename T, size_t N>
constexpr vector<T,N-1> make_sub(vector<T,N> const& vec, index_sequence<Is...>)
{
	return {get<Is>(vec)...};
}
} // namespace _impl

template<size_t Index, typename T, size_t N>
constexpr vector<T,N-1> sub(vector<T,N> const& vec)
{
	auto range = index_cat<
	        make_index_range<0,Index>,
	        make_index_range<Index+1,N>
	>{};

	return _impl::make_sub(vec, range);
}

//! Negate vector (reverse direction)
template<typename T, size_t N>
constexpr vector<T,N> operator-(vector<T,N> vec)
{
	return vec.negate();
}

//! Identity
template<typename T, size_t N>
constexpr vector<T,N> operator+(vector<T,N> vec)
{
	return vec;
}

//! Sum of two vectors
template<typename T, size_t N>
constexpr vector<T,N> operator+(vector<T,N> v1, vector<T,N> const& v2)
{
	v1 += v2;
	return v1;
}

//! Difference of two vectors
template<typename T, size_t N>
constexpr vector<T,N> operator-(vector<T,N> v1, vector<T,N> const& v2)
{
	v1 -= v2;
	return v1;
}

//! Scalar-vector product
template<typename T, size_t N>
vector<T,N> operator*(vector<T,N> vec, T const v)
{
	vec *= v;
	return vec;
}

//! Scalar-vector product
template<typename T, size_t N>
constexpr vector<T,N> operator/(vector<T,N> vec, T const v)
{
	vec /= v;
	return vec;
}

//! Scalar-vector product
template<typename T, size_t N>
constexpr vector<T,N> operator*(T const v, vector<T,N> vec)
{
	vec *= v;
	return vec;
}

//! Vector dot product
template<typename T, size_t N>
constexpr T operator*(vector<T,N> const& a, vector<T,N> const& b)
{
	return dot(a,b);
}

//! Get squared distance between two points
template<typename T, size_t N>
constexpr T distance_sq(vector<T,N> vec1, vector<T,N> const& vec2)
{
	return (vec1 - vec2).length_sq();
}

//! Get distance between two points
template<typename T, size_t N>
T distance(vector<T,N> vec1, vector<T,N> const& vec2)
{
	return (vec1 - vec2).length();
}

//! Get a normalized version of a vector
template<typename T, size_t N>
vector<T,N> normalize(vector<T,N> vec)
{
	return vec.normalize();
}

template<typename T, size_t N>
void fill(vector<T,N>& vec, T const value)
{
	std::fill(std::begin(vec.elems), std::end(vec.elems), value);
}
} // namespace math
} // namespace aw
#endif//aw_math_vector_h
