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
	pairs_iterator(Base1 const& iter1, Base2 const& iter2)
		: iters{iter1, iter2}
	{}

	std::pair<reference1,reference2> operator*()
	{
		return {*iters.first, *iters.second};
	}

	pairs_iterator& operator++()
	{
		++iters.first, ++iters.second;
	}

	bool operator!=(Base1 const& it)
	{
		return iters.first != it;
	}

	std::pair<Base1, Base2> iters;
};

template <typename Range1, typename Range2>
struct pairs_adapter {
private:
	using _iter1 = decltype(std::declval<Range1>().begin());
	using _iter2 = decltype(std::declval<Range2>().begin());
public:
	using iterator = pairs_iterator<_iter1, _iter2>;

	pairs_adapter(Range1&& range1, Range2&& range2)
		: ranges{range1, range2}
	{}

	iterator begin()
	{
		return {std::begin(ranges.first), std::begin(ranges.second)};
	}

	auto end()
	{
		return std::end(ranges.first);
	}

	std::pair<Range1&&, Range2&&> ranges;
};

/*!
 * Provides a way to iterate over two ranges in sync.
 * \note
 * Behavior is undefined if ranges have different sizes.
 */
template<typename... Ranges>
auto paired(Ranges&&... ranges)
{
	// assert((std::size(ranges) == ...));
	return pairs_adapter<Ranges...>(std::forward<Ranges>(ranges)...);
}
} // namespace aw
#endif//aw_utility_ranges_paired_h
