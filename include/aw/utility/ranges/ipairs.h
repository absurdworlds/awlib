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

template <typename Range>
struct ipairs_adapter {
private:
	using _iter_base = decltype(std::declval<Range>().begin());
public:
	using iterator = ipairs_iterator<_iter_base>;

	ipairs_adapter(Range&& range)
		: range(range)
	{}

	iterator begin()
	{
		return {std::begin(range)};
	}

	auto end()
	{
		return std::end(range);
	}

	Range&& range;
};

// TODO: starting index?
/*!
 * Keeps track of number of iterations.
 */
template<typename Range>
auto ipairs(Range&& range)
{
	return ipairs_adapter<Range>(std::forward<Range>(range));
}
} // namespace aw
#endif//aw_utility_ranges_ipairs_h
