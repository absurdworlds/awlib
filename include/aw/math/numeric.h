/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_numeric_h
#define aw_math_numeric_h
#include <limits>
namespace aw {
//! Number of radix digits in type T
template<typename T>
constexpr size_t num_digits = std::numeric_limits<T>::digits;

//! Wrapper for (x % 2) check
template<typename T>
constexpr bool is_odd(T value)
{
	return value & 1;
}

//! Wrapper for (x % 2 == 0) check
template<typename T>
constexpr bool is_even(T value)
{
	return !is_odd(value);
}
} //namespace aw
#endif //aw_math_numeric_h
