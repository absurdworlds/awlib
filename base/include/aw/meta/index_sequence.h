/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_index_sequence_h
#define aw_index_sequence_h
#include <utility>
#include <cstddef>
namespace aw {
template<size_t... I>
using index_sequence = std::index_sequence<I...>;

namespace _impl {
template<size_t Amount, typename Ind2>
struct index_shift;

template <size_t Amount, size_t... I>
struct index_shift<Amount, index_sequence<I...>> {
	using type = index_sequence<(Amount + I)...>;
};

template<typename Ind1, typename Ind2>
struct index_cat;

template<size_t... I1, size_t... I2>
struct index_cat<index_sequence<I1...>, index_sequence<I2...>> {
	using type = index_sequence<I1..., I2...>;
};
} // namespace _impl

template <size_t Size, typename Ind>
using index_shift = typename _impl::index_shift<Size, Ind>::type;

template <typename Ind1, typename Ind2>
using index_cat  = typename _impl::index_cat<Ind1, Ind2>::type;

//! Alias for std::make_index_sequence, for consistency
template <size_t Size>
using make_index_sequence = std::make_index_sequence<Size>;

//! Make sequence of all integers in range [End, Begin)
template <size_t Begin, size_t End>
using make_index_range = index_shift<Begin, make_index_sequence<End - Begin>>;
} // namespace aw
#endif//aw_index_sequence_h
