/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_is_iterable_h
#define aw_traits_is_iterable_h
#include <aw/meta/void_t.h>
#include <aw/meta/boolean.h>
namespace aw {
using std::declval;

namespace _impl {
template<class, typename = void> struct has_member_begin_end_t : false_type {};
template<class T>
struct has_member_begin_end_t<
	T,
	void_t<
		decltype( declval<T>().begin() ),
		decltype( declval<T>().end() )
	>
> : true_type {};

template<class, typename = void> struct has_non_member_begin_end_t : false_type {};
template<class T>
struct has_non_member_begin_end_t<
	T,
	void_t<
		decltype( begin(declval<T>()) ),
		decltype( end(declval<T>()) )
	>
> : true_type {};
} // namespace _impl


template<class T>
struct is_iterable_t : bool_or<
	_impl::has_member_begin_end_t<T>,
	_impl::has_non_member_begin_end_t<T>
> {};
template<typename T, size_t N>
struct is_iterable_t<T[N]> : true_type {};
template<typename T, size_t N>
struct is_iterable_t<T(&)[N]> : true_type {};

template<class T>
constexpr bool is_iterable = is_iterable_t<T>::value;

namespace _impl {
template<class, typename = void> struct has_member_cbegin_cend_t : false_type {};
template<class T>
struct has_member_cbegin_cend_t<
	T,
	void_t<
		decltype( declval<T>().cbegin() ),
		decltype( declval<T>().cend() )
	>
> : true_type {};

template<class, typename = void> struct has_non_member_cbegin_cend_t : false_type {};
template<class T>
struct has_non_member_cbegin_cend_t<
	T,
	void_t<
		decltype( cbegin(declval<T>()) ),
		decltype( cend(declval<T>()) )
	>
> : true_type {};
} // namespace _impl

template<class T>
struct is_const_iterable_t : bool_or<
	_impl::has_member_cbegin_cend_t<T>,
	_impl::has_non_member_cbegin_cend_t<T>
> {};
template<typename T, size_t N>
struct is_const_iterable_t<T[N]> : true_type {};
template<typename T, size_t N>
struct is_const_iterable_t<T(&)[N]> : true_type {};

template<class T>
constexpr bool is_const_iterable = is_const_iterable_t<T>::value;
} // namespace aw
#endif//aw_traits_is_iterable_h
