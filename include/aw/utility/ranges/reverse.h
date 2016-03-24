/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_reverse_adapter_h
#define aw_reverse_adapter_h
#include <utility>
#include <iterator>
namespace aw {
template <typename Container>
struct reverse_adapter {
	reverse_adapter(Container&& range)
		: range(range)
	{}
	Container& range;
};

template <typename T>
auto begin(reverse_adapter<T> v)
{
	return std::rbegin(v.range);
}

template <typename T>
auto end(reverse_adapter<T> v)
{
	return std::rend(v.range);
}

template <typename Container>
auto make_reverse(Container&& container)
{
	return reverse_adapter<Container>(std::forward<Container>(container));
}
} // namespace aw
#endif//aw_reverse_adapter_h
