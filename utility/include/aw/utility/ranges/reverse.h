/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_ranges_reverse_h
#define aw_utility_ranges_reverse_h
#include <utility>
#include <iterator>
namespace aw {
template <typename Range>
struct reverse_adapter {
	reverse_adapter(Range&& range)
		: range{range}
	{}

	auto begin() { return std::rbegin(range); }
	auto end()   { return std::rend(range); }

	Range range;
};

template<typename Range>
auto reverse(Range&& range)
{
	return reverse_adapter<Range>(std::forward<Range>(range));
}
} // namespace aw
#endif//aw_utility_ranges_reverse_h
