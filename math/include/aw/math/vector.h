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

namespace aw::math {
template <typename T, size_t N>
struct vector;

template<size_t I, typename T, size_t N>
constexpr T& get(vector<T,N>& vec);

template<size_t I, typename T, size_t N>
constexpr T const& get(vector<T,N> const& vec);

template<size_t I, typename T, size_t N>
constexpr T get(vector<T,N>&& vec) { return get<I>( vec ); }

template<size_t I, typename T, size_t N>
constexpr T get(vector<T,N> const&& vec) { return get<I>( vec ); }
} // namespace aw::math

namespace std {
template<typename T, size_t N>
class tuple_size< aw::math::vector<T,N> > : public std::integral_constant<size_t, N> {};
template<size_t I, typename T, size_t N>
class tuple_element< I, aw::math::vector<T,N> > { public: using type = T; };
} // namespace std

namespace aw {
namespace math {
namespace axis {
constexpr size_t x = 0;
constexpr size_t y = 1;
constexpr size_t z = 2;
constexpr size_t w = 3;
} // namespace axis

namespace _impl {
namespace vec {

template<typename A, typename B, size_t...Is>
constexpr void assign(A& a, B const& b, index_sequence<Is...>)
{
	(void(a[Is] = b[Is]), ...);
}

template<typename U, typename A, size_t...Is>
constexpr vector<U,sizeof...(Is)> cast(A const& a, index_sequence<Is...>)
{
	return { U(a[Is])... };
}

template<typename A, typename B, size_t...Is>
constexpr void add(A& a, B const& b, index_sequence<Is...>)
{
	(void(a[Is] += b[Is]), ...);
}

template<typename A, typename B, size_t...Is>
constexpr void sub(A& a, B const& b, index_sequence<Is...>)
{
	(void(a[Is] -= b[Is]), ...);
}

template<typename V, size_t...Is>
constexpr void mul(V& a, typename V::value_type const& v, index_sequence<Is...>)
{
	(void(a[Is] *= v), ...);
}

template<typename V, size_t...Is>
constexpr void div(V& a, typename V::value_type const& v, index_sequence<Is...>)
{
	(void(a[Is] /= v), ...);
}

template<typename V, size_t...Is>
constexpr auto dot(V const& vec1, V const& vec2, index_sequence<Is...>)
{
	using T = typename V::value_type;
	// FIXME: T{} workaround for GCC 6.1 bug
	T product = (T{vec1[Is]*vec2[Is]} + ...);
	return product;
}

template<typename B, typename A, size_t...Is>
constexpr B convert(A& a, index_sequence<Is...>)
{
	return { a[Is] ... };
}

template<typename V, typename Func, size_t...Is>
constexpr auto apply(V const& vec, Func func, index_sequence<Is...> is)
{
	using T = decltype( func(vec[0]) );
	return vector<T,sizeof...(Is)>{ func(vec[Is]) ... };
}

template<typename V, typename Func, size_t...Is>
constexpr void for_each(V& vec, Func func, index_sequence<Is...>)
{
	(func(vec[Is]), ...);
}
} // namespace vec
} // namespace _impl


template <typename T, size_t N>
struct vector {
	static_assert(N > 0, "Vector must have non-zero number of dimensions");

	constexpr static size_t vector_size = N;

	using value_type = T;

	static constexpr auto indices = make_index_sequence<N>{};

	value_type elems[N];

	constexpr vector& operator=(vector const& other)
	{
		_impl::vec::assign(*this, other, indices);
		return *this;
	}

	template<typename U>
	constexpr explicit operator vector<U,N>() const
	{
		return _impl::vec::cast<U>(*this, indices);
	}

	template<size_t M>
	constexpr vector& operator=(vector<T,M> const other)
	{
		static_assert(N > M);
		_impl::vec::assign(*this, other, other.indices);
		return *this;
	}

	constexpr vector& operator+=(vector const& other)
	{
		_impl::vec::add(*this, other, indices);
		return *this;
	}

	constexpr vector& operator-=(vector const& other)
	{
		_impl::vec::sub(*this, other, indices);
		return *this;
	}

	constexpr vector& operator*=(T const v)
	{
		_impl::vec::mul(*this, v, indices);
		return *this;
	}

	constexpr vector& operator/=(T const v)
	{
		_impl::vec::div(*this, v, indices);
		return *this;
	}

	constexpr vector& negate()
	{
		return (*this *= T(-1));
	}

	constexpr T dot(vector const& other) const
	{
		return _impl::vec::dot(*this, other, indices);
	}

	constexpr T length_sq() const
	{
		return dot(*this);
	}

	auto length() const
	{
		return math::sqrt(length_sq());
	}

	//! Normalize the vector
	vector& normalize()
	{
		T length = length_sq();
		if (length == 0)
			return *this;

		return (*this /= sqrt( length ));
	}

	constexpr T&       operator[](size_t idx)       { return elems[idx]; }
	constexpr T const& operator[](size_t idx) const { return elems[idx]; }

	constexpr T*       data()       { return elems; }
	constexpr T const* data() const { return elems; }

	constexpr T      (& array())[N]       { return elems; }
	constexpr T const(& array() const)[N] { return elems; }


	template<typename Func>
	constexpr vector& for_each(Func func)
	{
		_impl::vec::for_each(*this, func, indices);
		return *this;
	}

	template<typename Func>
	constexpr vector const& for_each(Func func) const
	{
		_impl::vec::for_each(*this, func, indices);
		return *this;
	}

	template<typename Func>
	constexpr auto apply(Func func) const
	{
		return _impl::vec::apply(*this, func, indices);
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

template<typename...Ts>
vector(Ts const&...) -> vector<std::common_type_t<Ts...>, sizeof...(Ts)>;
} // namespace math
} // namespace aw
#endif//aw_math_vector_h
