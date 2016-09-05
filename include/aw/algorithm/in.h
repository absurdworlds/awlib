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
#if !defined(_cpp_fold_expressions)
namespace _impl {
template<typename T>
bool in(T c, T c1)
{
	return c == c1;
}

template<typename T, typename... Args>
bool in(T c, T c1, Args&&... chars)
{
	return c == c1 || in(c, chars...);
}
}
#endif
/*!
 * Syntactic sugar for (val == v1) || (val == v2) || ...
 */
template<typename T, typename... Values>
bool in(T const& val, Values&&... v)
{
	static_assert(sizeof...(v), "");
#if __cpp_fold_expressions
	return ( bool(val == v) || ... );
#else
	return _impl::in(val, std::forward<Values>(v)...);
#endif
}
} // namespace aw
#endif//aw_algorithm_in_h
