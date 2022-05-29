/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_find_type_h
#define aw_meta_find_type_h
#include <limits>
#include <aw/types/types.h>
#include <aw/meta/list_ops.h>
#include <aw/meta/conditional.h>
namespace aw {
namespace meta {

namespace _impl {
template<typename Pred>
struct find_type {
	template<typename T>
	using F = aw::expand<Pred, T>;

	template <typename...Ts>
	struct result {
		using type = list<>;
	};

	template <typename T, typename...Ts>
	struct result<T,Ts...> {
		using type = conditional<F<T>::value, list<T,Ts...>, typename result<Ts...>::type>;
	};
};
} // namespace impl

template<typename Pred, typename...Ts>
using find_type = typename _impl::find_type<Pred>::template result<Ts...>::type;
} // namespace meta

template<typename Pred, typename...Ts>
using find_type = meta::head<meta::find_type<Pred,Ts...>>;
} // namespace aw
#endif//aw_meta_find_type_h
