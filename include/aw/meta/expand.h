/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_expand_h
#define aw_meta_expand_h
#include <aw/meta/placeholders.h>
namespace aw {
inline namespace meta {
namespace _impl {
template<typename F, typename...Args>
struct expand {
	using type = F;
};
} // namespace impl

/*!
 * Expand placeholders in metafunction.
 * For example:
 *     expand< is_same<_1, int>, int >
 * results in
 *     is_same<int, int>
 */
template<typename F, typename...Args>
using expand = typename expand<F,Args...>::type;


//-----------------------------------------------
namespace _impl {
template<template <typename...> class F, typename...Ts, typename...Args>
struct expand<F<Ts...>, Args...> {
	using type = F<expand<Ts,Args...>...>
};

template<typename T, typename...Args>
struct expand<_1, T, Args...>
{
	using type = T;
};

template<typename T, typename U, typename...Args>
struct expand<_2, T, U, Args...>
{
	using type = U;
};
} // namespace _impl
} // namespace meta
} // namespace aw
#endif//aw_meta_expand_h
