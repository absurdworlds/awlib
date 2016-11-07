/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_to_array_h
#define aw_types_to_array_h
#include <array>
#include <utility>
#include <aw/types/types.h>
#include <aw/types/traits/decay.h>
#include <aw/utility/index_sequence.h>
namespace aw {
using std::declval;

namespace array {
/*!\{
 * Convert arbitrary class supporting subscript operation to array.
 * Does not check if \a list has enough elements.
 */
template<typename L, size_t... Ns>
auto make(L&& list, index_sequence<Ns...>) ->
	std::array<decay<decltype(list[0])>, sizeof...(Ns)>
{
	return {list[Ns]...};
}

template<size_t N, typename L>
auto make(L&& list) ->
	std::array<decay<decltype(list[0])>, N>
{
	return make(std::forward<L>(list), make_index_sequence<N>{});
}

template<typename T, typename L, size_t... Ns>
auto convert(L&& list, index_sequence<Ns...>) ->
	std::array<T, sizeof...(Ns)>
{
	return {T(list[Ns])...};
}

template<typename T, size_t N, typename L>
auto convert(L&& list) -> std::array<T,N>
{
	return convert(std::forward<L>(list), make_index_sequence<N>{});
}
/*\}*/
} // namespace array
} // namespace aw
#endif//aw_types_to_array_h
