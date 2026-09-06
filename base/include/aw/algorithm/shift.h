#ifndef aw_algorithm_shift_h
#define aw_algorithm_shift_h

#include <algorithm>
#include <iterator>
#include <utility>

namespace aw {
/*!
 * Moves the range [from, from_end) to the position to.
 *
 * If from and to are the same, everything remains unchanged.
 *
 * \note to must not lie inside [from, from_end).
 */
template <typename Iterator>
void shift(Iterator from, Iterator from_end, Iterator to)
{
	if (from == from_end || from == to)
		return;

	if (std::next(from) == from_end) {
		auto val = std::move(*from);
		if (from < to)
			std::move(std::next(from), std::next(to), from);
		else
			std::move_backward(to, from, from_end);
		*to = std::move(val);
		return;
	}

	if (from < to)
		std::rotate(from, from_end, std::next(to));
	else
		std::rotate(to, from, from_end);
}

template <typename Iterator>
void shift(Iterator from, Iterator to, size_t n = 1)
{
	shift(from, std::next(from, n), to);
}

template <typename Container>
void shift(Container& c, size_t from, size_t to, size_t n = 1)
{
	shift(c.begin() + from, c.begin() + to, n);
}
} // namespace aw

#endif // aw_algorithm_shift_h
