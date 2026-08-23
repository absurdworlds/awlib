/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_join_h
#define aw_algorithm_join_h
#include <algorithm>
#include <aw/types/traits/iterator.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/meta/conditional.h>
namespace aw {
//! Assignment operator wrapper functor
template<typename T1, typename T2 = void>
struct assign_plus {
	constexpr T1& operator()(T1& a, T2 const& b) const
	{
		return a += b;
	}
};

template<typename T1>
struct assign_plus<T1, void> {
	template<typename T2>
	constexpr T1& operator()(T1& a, T2 const& bb) const
	{
		return a += bb;
	}
};

/*!
 * Join elements in range [begin, end) into single element,
 * starting with \a sink.
 * Adder must have signature of 
 *    T (T&, U const&)
 * where U must be convertible to T.
 */
template <typename Iterator, typename T, typename D, typename Adder>
T join(Iterator begin, Iterator end, T sink, D const& delim, Adder add)
{
	while (begin != end) {
		add(sink, delim);
		add(sink, *begin++);
	}
	return sink;
}

/*!
 * Same as above, but T::operator+= is used.
 */
template <typename Iterator, typename T, typename D>
auto join(Iterator begin, Iterator end, T sink, D const& delim) ->
	type_t<T, decltype(sink += delim)>
{
	return join(begin, end, sink, delim, assign_plus<T,D>{});
}

/*!
 * Join elements in range [begin, end) into single element,
 * where resulting elements are separated by \a delim.
 */
template <typename Iterator, typename T, typename Adder>
auto join(Iterator begin, Iterator end, T const& delim, Adder add) ->
	type_t<T, decltype(add(declval<T&>(), *begin++))>
{
	T sink;
	if (begin == end)
		return sink;
	add(sink, *begin++);
	return join(begin, end, sink, delim, add);
}

template <typename Iterator, typename T>
auto join(Iterator begin, Iterator end, T const& delim)
{
	return join(begin, end, delim, assign_plus<T>{});
}
} // namespace aw
#endif//aw_algorithm_join_h
