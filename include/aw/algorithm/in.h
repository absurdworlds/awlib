/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_in_h
#define aw_algorithm_in_h
#include <utility>
namespace aw {
/*!
 * Syntactic sugar for (val == v1) || (val == v2) || ...
 */
template<typename T, typename... Values>
bool in(T const& val, Values&&... v)
{
	static_assert(sizeof...(v), "");
	return ( bool(val == v) || ... );
}
} // namespace aw
#endif//aw_algorithm_in_h
