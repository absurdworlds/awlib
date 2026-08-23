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
#include "iter_range.h"

#include <iterator>
#include <utility>
namespace aw {
template <typename Iter1, typename Iter2>
struct pairs_sentinel : public std::pair<Iter1, Iter2> {
	using std::pair<Iter1, Iter2>::pair;
};

namespace adl {
using std::begin;
using std::end;
template<typename Range>
using begin_type = decltype( begin(std::declval<Range>()) );
template<typename Range>
using end_type   = decltype( end(std::declval<Range>()) );
} // namespace adl

template <typename Range1, typename Range2>
struct pairs_iterator {
private:
	using iterator1 = adl::begin_type<Range1>;
	using iterator2 = adl::begin_type<Range2>;

	using sentinel1 = adl::end_type<Range1>;
	using sentinel2 = adl::end_type<Range2>;

	using reference1 = typename std::iterator_traits<iterator1>::reference;
	using reference2 = typename std::iterator_traits<iterator2>::reference;

	using iter_pair = std::pair<iterator1, iterator2>;

	constexpr iter_pair make_pair()
	{
		using std::begin;
		return { begin(ranges.first), begin(ranges.second) };
	}

public:
	using iterator = pairs_iterator<Range1, Range2>;
	using sentinel = pairs_sentinel<sentinel1, sentinel2>;

	constexpr pairs_iterator(Range1&& first, Range2&& second)
		: ranges(std::forward<Range1>(first), std::forward<Range2>(second))
		, iters(make_pair())
	{}

	constexpr std::pair<reference1,reference2> operator*()
	{
		return {*iters.first, *iters.second};
	}

	constexpr pairs_iterator& operator++()
	{
		++iters.first, ++iters.second;
		return *this;
	}

	constexpr bool operator!=(sentinel const& other)
	{
		// If ranges have different lengths, we need to stop
		// at the end of the shortest range, && here is NOT a mistake
		return iters.first != other.first &&
		       iters.second != other.second;
	}

	constexpr bool operator!=(iterator1 const& it)
	{
		return iters.first != it;
	}

	constexpr iterator begin()
	{
		using std::begin;
		return *this;
	}

	constexpr sentinel end()
	{
		using std::end;
		return { end(ranges.first), end(ranges.second) };
	}

	constexpr iter_range<iterator1, sentinel1> first()
	{
		using std::end;
		return { iters.first, end(ranges.first) };
	}

	constexpr iter_range<iterator2, sentinel2> second()
	{
		using std::end;
		return { iters.second, end(ranges.second) };
	}

	// Safety thing for temporary ranges:
	// If an rvalue is passed to paired() it gets stored here
	std::pair<Range1, Range2> ranges;

	// Current state
	std::pair<iterator1, iterator2> iters;
};

/*!
 * Provides a way to iterate over two ranges in sync.
 * \note
 * Behavior is undefined if ranges have different sizes.
 */
template<typename... Ranges>
constexpr auto paired(Ranges&&... ranges)
{
	return pairs_iterator<Ranges...>(std::forward<Ranges>(ranges)...);
}
} // namespace aw
#endif//aw_utility_ranges_paired_h
