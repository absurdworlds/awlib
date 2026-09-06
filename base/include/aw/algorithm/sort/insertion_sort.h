#ifndef aw_algorithm_insertion_sort_h
#define aw_algorithm_insertion_sort_h

#include <aw/algorithm/insert_sorted.h>

namespace aw {
template<typename Iterator>
void insertion_sort( Iterator begin, Iterator end )
{
        if (begin == end)
                return;

	for ( auto it = std::next(begin); it != end; ++it ) {
		// note: doing the check here instead of just calling
		// insert_sorted_unguarded because GCC produces worse
		// code layout, making the already-sorted case 2x slower
		if ( *it < *std::prev(it) )
			_impl::insert_sorted_shift( begin, it );
        }
}

template<typename Container>
	requires std::bidirectional_iterator<typename Container::iterator>
void insertion_sort( Container& c )
{
	using std::begin;
	using std::end;
	insertion_sort( begin(c), end(c) );
}
} // namespace aw
#endif // aw_algorithm_insertion_sort_h
