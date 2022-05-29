/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_find_h
#define aw_algorithm_find_h
#include <algorithm>
namespace aw {
using std::find;
using std::find_if;
using std::find_if_not;

template<typename T>
struct is_not {
	T const& sample;
	bool operator()(T const& val) const
	{
		return val != sample;
	}
};

template<typename Iterator, typename T>
Iterator find_not(Iterator begin, Iterator end, T const& val)
{
	return find_if(begin, end, is_not<T>{val});
}
} // namespace aw
#endif//aw_algorithm_find_h
