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
namespace _impl {
/*
template<typename Pred>
struct find_index;
template<template <typename...> class Pred, typename...Args>
struct find_index<Pred<Args...>> {
*/

template<typename Pred>
struct find_index {
	template<typename T>
	using F = aw::expand<Pred, T>;

	template <size_t N, typename...Ts>
	struct index;

	template <size_t N, typename T>
	struct index<N,T> {
		static constexpr size_t value = F<T>::value ? N : std::numeric_limits<size_t>::max();
	};

	template <size_t N, typename T, typename...Ts>
	struct index<N,T,Ts...> {
		static constexpr size_t value = F<T>::value ? N : index<N+1,Ts...>::value;
	};

	/* Doesn't work with GCC: c++/71954
	template <size_t N, typename...Ts>
	static constexpr size_t value = std::numeric_limits<size_t>::max();

	template <size_t N, typename T>
	static constexpr size_t value<N,T> = F<T>::value ? N : value<N>;

	template <size_t N, typename T, typename...Ts>
	static constexpr size_t value<N,T,Ts...> = F<T>::value ? N : value<N+1,Ts...>;
	*/

	/*
	template <typename Head, typename...Tail>
	static constexpr size_t get_index(size_t idx = 0)
	{
		if constexpr(F<Head>::value)
			return idx;
		else if constexpr(sizeof...(Tail) == 0)
			return std::numeric_limits<size_t>::max();
		else
			return get_index<Tail...>(idx + 1);
	}*/
};
} // namespace impl

template<typename Pred, typename...Ts>
constexpr size_t find_index = _impl::find_index<Pred>::template index<0,Ts...>::value;
} // namespace aw
#endif//aw_meta_find_index_h
