/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_conditional
#define aw_traits_conditional
#include <utility>
#include <type_traits>
namespace aw {
/*!
 * Shorthand for std::enable_if
 *
 * Acts as type \a T if condition \a expr is met,
 * or as undefined type if it is not met.
 *
 * It is used to exclude template instantiations or overloads
 * from function overload resolution via SFINAE.
 *
 * See reference for std::enable_if.
 */
template<bool expr, typename T = void>
using enable_if = typename std::enable_if<expr, T>::type;

/*! Shorthand for enable_if with negated condition. */
template<bool expr, typename T = void>
using disable_if = typename std::enable_if<!expr, T>::type;

/*! Shorthand for enable_if<expr, void> */
template<bool expr>
using void_if = enable_if<expr,void>;

/*! Shorthand for enable_if<expr, bool> */
template<bool expr>
using bool_if = enable_if<expr,bool>;
} // namespace aw
#endif//aw_traits_conditional
