/*
 * Copyright (C) 2015-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_parameter_pack_h
#define aw_parameter_pack_h
#include <aw/types/types.h>
#include <aw/types/traits/conditional.h>
#include <aw/utility/index_sequence.h>
#include <aw/utility/fold.h>
namespace aw {
template <class Func, class... Args>
void for_each_argument(Func f, Args&&... args) {
	AW_FOLD(f(std::forward<Args>(args)));
}

template<class Func, size_t...Is>
void for_each_index(Func f, index_sequence<Is...>)
{
	for_each_argument(f, Is...);
}

template <class T, typename... Ts>
constexpr bool is_in_pack = bool_or<std::is_same<T,Ts>::value...>;
} // namespace aw
#endif//aw_parameter_pack_h
