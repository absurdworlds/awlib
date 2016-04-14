/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_enable_if
#define aw_traits_enable_if
#include <utility>
#include <type_traits>
namespace aw {
template<bool expr, typename T>
using enable_if = typename std::enable_if<expr, T>::type;

template<bool expr, typename T>
using disable_if = typename std::enable_if<!expr, T>::type;

template<bool expr>
using void_if = enable_if<expr,void>;

template<bool expr>
using bool_if = enable_if<expr,bool>;
} // namespace aw
#endif//aw_traits_enable_if
