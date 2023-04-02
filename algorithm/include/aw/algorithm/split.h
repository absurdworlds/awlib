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
 * \brief Slices range [begin, end) into subranges by delimiter, including empty subranges.
 *
 * This function divides the input into subranges by the provided delimiter,
 * and calls \a store for each subrange. It includes empty subranges
 * that might result from consecutive delimiters.
 *
 * \param begin An iterator pointing to the beginning of the input range.
 * \param end An iterator pointing to the end of the input range.
 * \param delim The delimiter used to slice the input range into subranges.
 * \param store A function or functor that stores the resulting subranges.
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
 * \brief Splits range [begin, end) into subranges by delimiter, excluding empty subranges.
 *
 * This function divides the input into subranges by the provided delimiter,
 * and calls \a store for each subrange. Empty subranges resulting from multiple
 * consecutive delimiters are skipped.
 *
 * \param begin An iterator pointing to the beginning of the input range.
 * \param end An iterator pointing to the end of the input range.
 * \param delim The delimiter used to slice the input range into subranges.
 * \param store A function or functor that stores the resulting subranges.
 */
template <typename Iterator, typename T, typename Store>
void split(Iterator begin, Iterator end, T const& delim, Store store)
{
	Iterator pos1;
	Iterator pos2 = begin;

	do {
		pos1 = find_not(pos2, end, delim);

		if (pos1 == end)
			break;

		pos2 = find(pos1, end, delim);
		store(pos1, pos2);
	} while (true);
}
} // namespace aw
#endif//aw_algorithm_split_h
