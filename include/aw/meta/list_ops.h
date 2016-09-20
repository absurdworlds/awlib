/*
 * Copyright (C) 2015-2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_list_ops_h
#define aw_meta_list_ops_h
#include <aw/meta/list.h>
#include <aw/meta/expand.h>
#include <aw/types/traits/basic_traits.h>
namespace aw {
/*! Check if type T is present in parameter pack Ts */
template <class T, typename... Ts>
constexpr bool is_in_pack      = (is_same<T,Ts> || ...);
/*! Count how many times T occurs in parameter pack Ts */
template <class T, typename... Ts>
constexpr size_t count_in_pack = (size_t(is_same<T,Ts>) + ...);

namespace meta {
template<typename F, typename...Ts>
constexpr bool match_any = (expand<F, Ts>::value || ...);

template<typename F, typename...Ts>
constexpr bool match_all = (expand<F, Ts>::value && ...);

template<typename F, typename...Ts>
constexpr size_t count_if = (size_t(expand<F, Ts>::value) + ...);




template<typename L>
using head = typename _impl::head<L>::type;
template<typename L>
using tail = typename _impl::tail<L>::type;


/*! Checks that L1 is subset of L2.*/
template<typename L1, typename L2>
struct is_subset;
template<typename... L1, typename... L2>
struct is_subset<list<L1...>, list<L2...>> {
	static constexpr bool value = (is_in_pack<L1,L2...> && ...);
};
} // namespace meta

template<typename L1, typename L2>
constexpr bool is_subset = meta::is_subset<L1, L2>::value;
} // namespace aw
#endif//aw_meta_list_ops_h
