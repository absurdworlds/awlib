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
template<typename Pred, typename... Ts>
constexpr std::size_t find_index()
{
	constexpr bool eval[] { aw::expand_r<Pred, Ts>::value..., false };
	for (std::size_t i = 0; i < sizeof...(Ts); ++i)
		if (eval[i])
			return i;
	return invalid_index;
}
} // namespace impl

template<typename Pred, typename...Ts>
constexpr size_t find_index = _impl::find_index<Pred, Ts...>();
} // namespace meta

// TODO: remove
using meta::find_index;
} // namespace aw
#endif//aw_meta_find_index_h
