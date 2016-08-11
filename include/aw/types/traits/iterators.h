/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_iterators
#define aw_traits_iterators
#include <iterator>
#include <aw/types/traits/basic_traits.h>
namespace aw {
template<typename Iterator>
constexpr bool is_input_iter = std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::input_iterator_tag
>::value;

template<typename Iterator>
constexpr bool is_forward_iter = std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::forward_iterator_tag
>::value;
} // namespace aw
#endif//aw_traits_iterators
