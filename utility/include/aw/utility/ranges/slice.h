/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_slice_adapter_h
#define aw_slice_adapter_h
#include <cassert>
#include <utility>
#include <iterator>
namespace aw {
template <typename Container>
struct slice_adapter {
	slice_adapter(Container&& range, size_t start, size_t end)
		: range(range), bounds{start, range.size() - end}
	{}
	Container& range;

	std::pair<size_t,size_t> bounds;
};

template <typename T>
auto begin(slice_adapter<T>& v)
{
	return std::begin(v.range) + v.bounds.first;
}

template <typename T>
auto end(slice_adapter<T>& v)
{
	return std::end(v.range) - v.bounds.second;
}

template <typename Container>
auto slice_range(Container&& container, size_t start)
{
	assert(start <= container.size());

	return slice_adapter<Container> {
		std::forward<Container>(container),
		start,
		container.size()
	};
}

template <typename Container>
auto slice_range(Container&& container, size_t start, size_t length)
{
	assert(start <= container.size());
	assert(start+length <= container.size());

	return slice_adapter<Container>{
		std::forward<Container>(container),
		start,
		start+length
	};
}
} // namespace aw
#endif//aw_slice_adapter_h
