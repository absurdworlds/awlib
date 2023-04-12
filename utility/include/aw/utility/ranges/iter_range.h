/*
 * Copyright (C) 2023  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_ranges_iter_range_h
#define aw_utility_ranges_iter_range_h
#include <utility>
#include <iterator>
namespace aw {
template <typename Iterator, typename Sentinel>
struct iter_range {
	using iterator = Iterator;

	Iterator begin_iter;
	Sentinel end_iter;

	auto begin() { return begin_iter; }
	auto end() { return end_iter; }
};
} // namespace aw
#endif//aw_utility_ranges_iter_range_h
