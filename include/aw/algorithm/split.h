/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_split_h
#define aw_algorithm_split_h
#include <aw/types/traits/iterator.h>
#include <aw/algorithm/find.h>
namespace aw {
/*!
 * Slices range [begin, end) into subranges by delimiter,
 * including empty subranges.
 */
template <typename Iterator, typename T, typename Store>
void cut(Iterator begin, Iterator end, T const& delim, Store store)
{
	do {
		Iterator pos = find(begin, end, delim);
		store(begin, pos);

		if (pos == end)
			break;

		begin = std::next(pos);
	} while (true);
}

/*!
 * Splits range [begin, end) into subranges by delimiter,
 * excluding empty subranges.
 */
template <typename Iterator, typename T, typename Store>
void split(Iterator begin, Iterator end, T const& delim, Store store)
{

	auto pos1 = find_not(begin, end, delim);
	auto pos2 = find(pos1, end, delim);

	while (pos1 != end) {
		store(pos1, pos2);

		pos1 = find_not(pos2, end, delim);
		pos2 = find(pos1, end, delim);
	}
}
} // namespace aw
#endif//aw_algorithm_split_h
