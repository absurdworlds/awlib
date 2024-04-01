/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_basic_operations_h
#define aw_traits_basic_operations_h
#include <aw/meta/is_same.h>
#include <aw/meta/void_t.h>
namespace aw {
using std::declval;

template<typename T> using increment   = decltype( ++declval<T&>() );
template<typename T> using decrement   = decltype( --declval<T&>() );
template<typename T> using dereference = decltype( *declval<T>() );

template<typename T, typename = void>
constexpr bool is_incrementable = false;
template<typename T>
constexpr bool is_incrementable< T, void_t<increment<T>> > {
	is_same_v< increment<T>, T&>
};

template<typename T, typename = void>
constexpr bool is_decrementable = false;
template<typename T>
constexpr bool is_decrementable< T, void_t<decrement<T>> > {
	is_same_v< decrement<T>, T&>
};

template<typename T, typename = void>
constexpr bool is_dereferencable = false;
template<typename T>
constexpr bool is_dereferencable< T, void_t< dereference<T> > > = true;
} // namespace aw
#endif//aw_traits_basic_operations_h
