/*
 * Copyright (C) 2015-2017  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_substitute_h
#define aw_meta_substitute_h
namespace aw {
namespace meta {
namespace _impl {
template<template<typename...> class T, typename S>
struct substitute;

template<template<typename...> typename T,
         template<typename...Ts> typename S,
         typename...Ts>
struct substitute<T, S<Ts...>> {
	using type = T<Ts...>;
};
} // namespace _impl

/*!
 * Substitute template S with template T, while keeping the arguments.
 * Example:
 * `substitute<tuple, meta::list<int,float>>` yields `tuple<int,float>`
 */
template<template<typename...> typename T, typename S>
using substitute = typename _impl::substitute<T,S>::type;
} // namespace meta
} // namespace aw
#endif//aw_meta_substitute_h
