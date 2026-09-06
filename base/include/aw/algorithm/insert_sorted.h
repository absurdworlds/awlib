#ifndef aw_algorithm_insert_sorted_h
#define aw_algorithm_insert_sorted_h

#include <algorithm>
#include <iterator>
#include <utility>

namespace aw {
namespace _impl {
/*!
* Moves *pos into place within the sorted range [begin, pos).
*
* Requires that *pos is not already in its place and
* [begin, pos) to be a non-empty range.
*/
template<typename Iterator>
void insert_sorted_shift(Iterator begin, Iterator pos)
{
	auto val = std::move(*pos);
	if ( val < *begin ) {
		std::move_backward( begin, pos, std::next(pos) );
		*begin = std::move(val);
	} else {
		// val does not precede the *begin, so we can skip the bounds checks
		auto hole = pos;
		auto prev = std::prev(pos);
		do {
			*hole = std::move(*prev);
			hole = prev;
			prev = std::prev(prev);
		} while ( val < *prev );
		*hole = std::move(val);
	}
}
} // namespace __impl

//! same as insert_sorted for callers that already know pos != begin
template<typename Iterator>
void insert_sorted_unguarded(Iterator begin, Iterator pos)
{
	if ( !(*pos < *std::prev(pos)) )
		return;
	_impl::insert_sorted_shift(begin, pos);
}

/*!
 * Moves the element at \a pos backwards into place within the
 * sorted range [begin, pos), shifting the elements it passes
 * one position right.
 *
 * The element ends up after any elements equal to it.
 */
template<typename Iterator>
void insert_sorted(Iterator begin, Iterator pos)
{
	if (pos == begin)
		return;
	insert_sorted_unguarded(begin, pos);
}
} // namespace aw
#endif // aw_algorithm_insert_sorted_h
