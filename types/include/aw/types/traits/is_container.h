/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_is_container
#define aw_traits_is_container
#include <utility>
#include <aw/meta/void_t.h>
namespace aw {
template<class, typename = void>
struct is_basic_container_t : std::false_type {};

template<class T>
struct is_basic_container_t<
	T,
	void_t<
		typename T::value_type,
		typename T::size_type,
		typename T::iterator,
		typename T::const_iterator,
		decltype( declval<T>().size() ),
		decltype( declval<T>().empty() ),
		decltype( declval<T>().begin() ),
		decltype( declval<T>().end() ),
		decltype( declval<T>().cbegin() ),
		decltype( declval<T>().cend() )
	>
> : std::true_type {};

template<class, typename = void>
struct is_allocator_aware_t : std::false_type {};

template<class T>
struct is_allocator_aware_t<
	T,
	void_t<
		typename T::allocator_type,
		decltype( declval<T>().get_allocator() )
	>
> : std::true_type {};

template<class T>
constexpr bool is_allocator_aware = is_basic_container_t<T>::value;

template<class T>
constexpr bool is_basic_container = is_basic_container_t<T>::value;

template<class T> constexpr bool is_allocator_aware_container =
	is_basic_container<T> && is_allocator_aware<T>;
} // namespace aw
#endif//aw_traits_is_container
