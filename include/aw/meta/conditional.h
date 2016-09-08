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
inline namespace meta {
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


/*! Alias for std::conditional */
template<bool expr, typename T, typename F>
using conditional = typename std::conditional<expr, T, F>::type;

#if __cpp_fold_expressions >= 201411L
template<bool... Bools>
constexpr bool bool_and = (Bools && ...);

template<bool... Bools>
constexpr bool bool_or  = (Bools || ...);

#else
namespace _impl {
template<bool... Bools>
struct bool_and : std::true_type { };

template<bool Bool, bool... Bools>
struct bool_and<Bool, Bools...>
	: conditional<Bool, bool_and<Bools...>, std::false_type>
{ };

template<bool... Bools>
struct bool_or : std::false_type { };

template<bool Bool, bool... Bools>
struct bool_or<Bool, Bools...>
	: conditional<Bool, std::true_type, bool_or<Bools...>>
{ };
} // namespace _impl

/*!
 * @{
 * Apply logical operators to list of \a Bools.
 * Used to substitute fold expressions when those are not available.
 */
template<bool... Bools>
constexpr bool bool_and = _impl::bool_and<Bools...>::value;

template<bool... Bools>
constexpr bool bool_or = _impl::bool_or<Bools...>::value;
//!@}
#endif
} // inline namespace meta
} // namespace aw
#endif//aw_traits_conditional
