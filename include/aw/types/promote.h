/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_promote
#define aw_types_promote
#include<aw/types/types.h>
namespace aw {
namespace _impl {
template <typename T> struct Promote;

template<> struct Promote<i8>  { using type = i16; };
template<> struct Promote<i16> { using type = i32; };
template<> struct Promote<i32> { using type = i64; };
template<> struct Promote<i64> { using type = i64; };

template<> struct Promote<u8>  { using type = u16; };
template<> struct Promote<u16> { using type = u32; };
template<> struct Promote<u32> { using type = u64; };
template<> struct Promote<u64> { using type = u64; };

template<> struct Promote<f32> { using type = f64; };
template<> struct Promote<f64> { using type = f64; };
} // namespace _impl

//! Promote arithmetic type to a next larger type (if available)
template <typename T>
using Promote = typename _impl::Promote<T>::type;
} // namespace aw
#endif//aw_types_promote
