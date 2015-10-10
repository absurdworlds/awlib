/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_range_adaptors_
#define _awrts_range_adaptors_
namespace awrts {
template <typename T>
struct reverse_adapter {
	reverse_adapter(T& range)
		: range(range)
	{}
	T& range;
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

template <typename T>
reverse_adapter<T> make_reverse(T&& container)
{
	return reverse_adapter<T> (container);
}
} // namespace awrts
#endif//_awrts_range_adaptors_
