/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_find_index_h
#define aw_meta_find_index_h
#include <limits>
#include <aw/types/types.h>
#include <aw/meta/expand.h>
namespace aw {
namespace meta {

constexpr size_t invalid_index = std::numeric_limits<size_t>::max();

namespace _impl {
template<typename Pred>
struct find_index {
	template<typename T>
	using F = aw::expand_r<Pred, T>;

	template <size_t N, typename...Ts>
	struct index;

	template <size_t N, typename T>
	struct index<N,T> {
		static constexpr size_t value = F<T>::value ? N : invalid_index;
	};

	template <size_t N, typename T, typename...Ts>
	struct index<N,T,Ts...> {
		static constexpr size_t value = F<T>::value ? N : index<N+1,Ts...>::value;
	};
};
} // namespace impl

template<typename Pred, typename...Ts>
constexpr size_t find_index = _impl::find_index<Pred>::template index<0,Ts...>::value;
} // namespace meta

// TODO: remove
using meta::find_index;
} // namespace aw
#endif//aw_meta_find_index_h
