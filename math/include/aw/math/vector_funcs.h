/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_vector_funcs_h
#define aw_math_vector_funcs_h
#include <aw/math/vector.h>
#include <aw/math/trigonometry.h>
namespace aw {
namespace math {

template<typename T, size_t N>
vector<T,N> sin( vector<T,N> vec )
{
	auto func = [] (T val) { return sin( radians<T>{val} ); };
	return vec.apply( func );
}

template<typename T, size_t N>
vector<T,N> cos( vector<T,N> vec )
{
	auto func = [] (T val) { return cos( radians<T>{val} ); };
	return vec.apply( func );
}

template<typename R, typename P, size_t N>
vector<R,N> sin( vector<angle<R,P>,N> vec )
{
	auto func = [] (angle<R,P> val) { return sin( val ); };
	return vec.apply( func );
}

template<typename R, typename P, size_t N>
vector<R,N> cos( vector<angle<R,P>,N> vec )
{
	auto func = [] (angle<R,P> val) { return cos( val ); };
	return vec.apply( func );
}

} // namespace math
} // namespace aw
#endif//aw_math_vector_funcs_h
