/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_binary_find_h
#define aw_algorithm_binary_find_h
#include <algorithm>
namespace aw {
/*!
 * Finds the first element in the range [first, last) that matches value \a val
 *
 * Requires that the input range is at least partially ordered.
 *
 * Takes a comparator function \a comp.
 */
template <typename Iterator, typename T, typename Comparator>
Iterator binary_find(Iterator begin, Iterator end, T const& val, Comparator comp)
{
	Iterator pos = std::lower_bound(begin, end, val, comp);
	if (pos == end || comp(*pos, val))
		return end;
	return pos;
}

/*!
 * Same as previous overload, but uses operator< instead of comparator.
 */
template <typename Iterator, typename T>
Iterator binary_find(Iterator begin, Iterator end, T const& val)
{
	return binary_find(begin, end, val, std::less<T>{});
}
} // namespace aw
#endif//aw_algorithm_binary_find_h
