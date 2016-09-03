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
namespace aw {
//! Assignment operator wrapper functor
template<typename T1, typename T2>
struct assign_plus {
	constexpr T1& operator()(T1& a, T2 const& b) const
	{
		return a += b;
	}
};

/*!
 * Join elements in range [begin, end) into single element,
 * starting with \a sink.
 * Adder must have signature of 
 *    T (T&, U const&)
 * where U must be convertible to T.
 */
template <typename Iterator, typename T, typename Adder>
T join(Iterator begin, Iterator end, T sink, T const& delim, Adder add)
{
	while (begin != end) {
		add(sink, delim);
		add(sink, *begin++);
	}
	return sink;
}

/*
 * Same as above, but T::operator+= is used.
 */
template <typename Iterator, typename T>
T join(Iterator begin, Iterator end, T sink, T const& delim)
{
	return join(begin, end, sink, delim, assign_plus<T,T>{});
}

/*
 * Join elements in range [begin, end) into single element,
 * where resulting elements are separated by \a delim.
 */
template <typename Iterator, typename T, typename Adder>
T join(Iterator begin, Iterator end, T const& delim, Adder add)
{
	T sink;
	if (begin == end)
		return sink;
	add(sink, *begin++);
	return join(begin, end, sink, delim);
}

template <typename Iterator, typename T>
T join(Iterator begin, Iterator end, T const& delim)
{
	return join(begin, end, delim, assign_plus<T,T>{});
}
} // namespace aw
#endif//aw_algorithm_join_h
