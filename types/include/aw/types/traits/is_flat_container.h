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
template<class T, typename = void>
struct is_flat_container_t : std::false_type {};

template<class T>
struct is_flat_container_t<
	T,
	void_t<
		decltype( declval<T>().size() ),
		decltype( declval<T>().data() )
	>
> : std::true_type {};

template<typename C, typename T, typename = void>
struct is_flat_container_of : std::false_type {};

template<typename C, typename T>
struct is_flat_container_of<
	C, T,
	void_t<
		decltype( declval<C>().size() ),
		decltype( declval<C>().data() )
	>
> : std::is_convertible<decltype( declval<C>().data() ), T*> {};

template<class T>
constexpr bool is_flat_container = is_flat_container_t<T>::value;

template<typename C, typename T>
constexpr bool is_flat_container_of_v = is_flat_container_of<C,T>::value;
} // namespace aw
#endif//aw_traits_is_container
