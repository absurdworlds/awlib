/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_at_index_h
#define aw_meta_at_index_h
#include <aw/types/types.h>
namespace aw {
inline namespace meta {
namespace _impl {
// TODO: profiling
// http://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
// https://metaporky.blogspot.ru/2016/09/meta-monads.html
template<bool Found>
struct at_index {
	template<size_t I, typename T, typename...Ts>
	using type = typename at_index<I == 0>::template type<I - 1, Ts...>
};

template<>
struct at_index<true> {
	template<size_t I, typename T, typename...Ts>
	using type = T;
};
} // namespace _impl

template<size_t I, typename...Ts>
using at_index = typename _impl::at_index<I == 0>::template type<I, Ts...>;
} // namespace meta
} // namespace aw
#endif//aw_meta_at_index_h
