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
#include <aw/meta/conditional.h>
namespace aw {
template<typename Iterator>
using require_input_iterator = enable_if<is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::input_iterator_tag
>>;

template<typename Iterator>
constexpr bool is_input_iterator = is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::input_iterator_tag
>;

template<typename Iterator>
constexpr bool is_forward_iterator = std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::forward_iterator_tag
>::value;

template<typename Iterator>
constexpr bool is_bidirectional_iterator = std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::bidirectional_iterator_tag
>::value;

template<typename Iterator>
constexpr bool is_random_access_iterator = std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category,
	std::random_access_iterator_tag
>::value;
} // namespace aw
#endif//aw_traits_iterators
