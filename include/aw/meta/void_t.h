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

template<typename T, typename...Ts> struct make_type { using type = T; };
template<typename T, typename...Ts>  using type_t = typename make_type<T,Ts...>::type;
template<typename... Ts> using void_t = type_t<void,Ts...>;
} // namespace aw
#endif//aw_traits_void_t
