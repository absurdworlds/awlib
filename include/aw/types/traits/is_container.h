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
#include <type_traits>
namespace aw {
namespace detail {
template<typename, typename = void>
struct IsContainer : std::false_type {};

template<typename T>
struct IsContainer<
	T,
	void_t<
		typename T::value_type,
		typename T::size_type,
		typename T::allocator_type,
		typename T::iterator,
		typename T::const_iterator,
		decltype(std::declval<T>().size()),
		decltype(std::declval<T>().begin()),
		decltype(std::declval<T>().end()),
		decltype(std::declval<T>().cbegin()),
		decltype(std::declval<T>().cend())
	>
> : public std::true_type {};
} // namespace detail

constexpr auto IsContainer = detail::IsContainer<T>::value;
} // namespace aw
#endif//aw_traits_is_container
