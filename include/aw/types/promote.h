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
#include <aw/meta/void_t.h>
#include <aw/types/types.h>
#include <aw/types/int128.h>
namespace aw {
namespace _impl {
template <typename T> struct promote;

template<> struct promote<i8>  { using type = i16; };
template<> struct promote<i16> { using type = i32; };
template<> struct promote<i32> { using type = i64; };
#if AW_FEATURE(SIGNED128)
template<> struct promote<i64> { using type = i128; };
#endif

template<> struct promote<u8>  { using type = u16; };
template<> struct promote<u16> { using type = u32; };
template<> struct promote<u32> { using type = u64; };
#if AW_FEATURE(UNSIGNED128)
template<> struct promote<u64> { using type = u128; };
#endif

template<> struct promote<f32> { using type = f64; };
} // namespace _impl



//! Promote arithmetic type to a next larger type (if available)
template <typename T>
using promote = typename _impl::promote<T>::type;



namespace _impl {
template <typename T, typename = void>
struct can_promote : std::false_type {};

template <typename T>
struct can_promote<T, void_t<aw::promote<T>>> : std::true_type {};
} // namespace _impl


//! True if promote<T> can be used
template<typename T>
constexpr bool can_promote = _impl::can_promote<T>::value;

/*!
 * Unsigned counterpart to T.
 * If T is already unsigned, T is unchanged.
 */
template<typename T>
using make_unsigned = typename std::make_unsigned<T>::type;

/*!
 * Signed counterpart to T.
 * If T is already signed, T is unchanged.
 */
template<typename T>
using make_signed = typename std::make_signed<T>::type;
} // namespace aw
#endif//aw_types_promote
