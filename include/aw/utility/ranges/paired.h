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
namespace aw {
template <typename Base1, typename Base2>
struct pairs_iterator {
private:
	using reference1 = typename std::iterator_traits<Base1>::reference;
	using reference2 = typename std::iterator_traits<Base2>::reference;

public:
	constexpr pairs_iterator(Base1 iter1, Base2 iter2)
		: iters{iter1, iter2}
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

	constexpr bool operator!=(pairs_iterator const& other)
	{
		return iters != other.iters;
	}

	constexpr bool operator!=(Base1 const& it)
	{
		return iters.first != it;
	}

	std::pair<Base1, Base2> iters;
};

namespace adl {
using std::begin;
using std::end;
template<typename Range>
using begin_type = decltype( begin(std::declval<Range>()) );
template<typename Range>
using end_type   = decltype( begin(std::declval<Range>()) );
} // namespace

template <typename Range1, typename Range2>
struct pairs_adapter {
private:
	using _iter1 = adl::begin_type<Range1>;
	using _iter2 = adl::begin_type<Range2>;
public:
	using iterator = pairs_iterator<_iter1, _iter2>;

	constexpr pairs_adapter(Range1 range1, Range2 range2)
		: ranges{range1, range2}
	{}

	constexpr iterator begin()
	{
		using std::begin;
		return {begin(ranges.first), begin(ranges.second)};
	}

	constexpr iterator end()
	{
		using std::end;
		return {end(ranges.first), end(ranges.second)};
	}

	std::pair<Range1, Range2> ranges;
};

/*!
 * Provides a way to iterate over two ranges in sync.
 * \note
 * Behavior is undefined if ranges have different sizes.
 */
template<typename... Ranges>
constexpr auto paired(Ranges&&... ranges)
{
	return pairs_adapter<Ranges...>(std::forward<Ranges>(ranges)...);
}
} // namespace aw
#endif//aw_utility_ranges_paired_h
