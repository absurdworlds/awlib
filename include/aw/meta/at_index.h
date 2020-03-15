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
namespace _impl {
// TODO: profiling
// http://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
// https://metaporky.blogspot.ru/2016/09/meta-monads.html
template<size_t I, typename T, typename...Ts>
struct at_index_t {
	using type = typename at_index_t<I-1, Ts...>::type;
};

template<typename T, typename...Ts>
struct at_index_t<0,T,Ts...> {
	using type = T;
};
} // namespace _impl

template<size_t I, typename...Ts>
using at_index = typename _impl::at_index_t<I,Ts...>::type;
} // namespace aw
#endif//aw_meta_at_index_h
