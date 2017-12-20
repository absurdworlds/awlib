/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_ranges_paired_h
#define aw_utility_ranges_paired_h
#include <utility>
#include <iterator>

#include "zip.h"

namespace aw {

namespace adl {
using std::begin;
using std::end;
template<typename Range>
using begin_type = decltype( begin(std::declval<Range>()) );
template<typename Range>
using end_type   = decltype( begin(std::declval<Range>()) );
} // namespace

/*!
 * Provides a way to iterate over two ranges in sync.
 * \note
 * Behavior is undefined if ranges have different sizes.
 */
template<typename... Ranges>
constexpr auto paired(Ranges&&... ranges)
{
	return zip{std::forward<Ranges>(ranges)...};
}
} // namespace aw
#endif//aw_utility_ranges_paired_h
