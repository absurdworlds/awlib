/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_ranges_ipairs_h
#define aw_utility_ranges_ipairs_h
#include <utility>
#include <iterator>
namespace aw {
template <typename Base>
struct ipairs_iterator {
	ipairs_iterator(Base const& iter)
		: iter{iter}
	{}

	using value_type = typename std::iterator_traits<Base>::value_type;
	using reference  = typename std::iterator_traits<Base>::reference;

	std::pair<size_t,reference> operator*()
	{
		return {idx,*iter};
	}

	ipairs_iterator& operator++()
	{
		++iter, ++idx;
	}

	bool operator!=(Base const& it)
	{
		return iter != it;
	}

	size_t idx = 0;
	Base iter;
};

// TODO: starting index?
template <typename Range>
struct ipairs {
	ipairs(Range&& range)
		: range(range)
	{}

	auto begin()
	{
		return ipairs_iterator{ std::begin(range) };
	}

	auto end()
	{
		return std::end(range);
	}

	Range&& range;

	using iterator = decltype( std::declval<ipairs>().begin() );
};

/*!
 * Keeps track of number of iterations.
 */
template<typename Range>
ipairs(Range&& range) -> ipairs<Range>;
} // namespace aw
#endif//aw_utility_ranges_ipairs_h
