/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_void_t
#define aw_traits_void_t
#include <type_traits>
namespace aw {
using std::declval;

/*!
 * Generalization of std::void_t.
 *
 * Has some other uses, for example, to "gather" type together:
 * std::byte data[8] -> type_t<std::byte[8]> data;
 * (useful when working with macros)
 */
template<typename T, typename...Ts>  using type_t = T;

/*!
 * Alias for std::void_t:
 * Utility metafunction that maps a sequence of any types to the type void
 */
template<typename... Ts> using void_t = type_t<void,Ts...>;
} // namespace aw
#endif//aw_traits_void_t
