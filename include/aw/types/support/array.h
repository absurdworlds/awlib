/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_array_h
#define aw_types_array_h
#include <array>
#include <tuple>
#include <utility>
namespace aw {
namespace _impl {
template<typename T, size_t... I>
std::array<T,sizeof...(I)+1>
extend_array(std::array<T,sizeof...(I)>&& array, std::index_sequence<I...>)
{
	return {array[I]..., 0};
}


template<typename L, typename T, size_t... I>
std::array<L,sizeof...(I)>
convert_array(std::array<T,sizeof...(I)>&& array, std::index_sequence<I...>)
{
	return {array[I]...};
}
} // namespace _impl


template<typename T, size_t N>
[[deprecated]] std::array<T,N+1> extend_array(std::array<T,N>&& array)
{
	auto index = std::make_index_sequence<N>{};
	return _impl::extend_array(std::forward<std::array<T,N>>(array), index);
}

template<typename L, typename T, size_t N>
std::array<L,N> convert_array(std::array<T,N>&& array)
{
	auto index = std::make_index_sequence<N>{};
	return _impl::convert_array<L>(std::forward<std::array<T,N>>(array), index);
}


template <typename Head, typename...Tail>
auto make_array(Head arg, Tail...args)
{
	std::array<Head, sizeof...(Tail)+1> values = { arg, args... };
	return values;
}

namespace _impl {
template <size_t... I, typename T, size_t N>
auto to_tuple(std::array<T,N> array, std::index_sequence<I...>)
{
	return std::tuple{array[I]...};
}
} // namespace _impl

template <typename T, size_t N>
auto to_tuple(std::array<T,N> array)
{
	return _impl::to_tuple(array, std::make_index_sequence<N>{});
}
} // namespace aw
#endif//aw_types_array_h
