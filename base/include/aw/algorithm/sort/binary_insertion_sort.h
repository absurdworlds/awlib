#ifndef aw_algorithm_binary_insertion_sort_h
#define aw_algorithm_binary_insertion_sort_h

#include <aw/algorithm/shift.h>

namespace aw {
template<typename Iterator>
void binary_insertion_sort( Iterator begin, Iterator end )
{
        if (begin == end)
                return;
        for ( auto it = std::next( begin ); it != end; ++it) {
	    const auto prev = std::prev(it);
	    if ( !(*it < *prev) )
		    continue;
            const auto pos = std::upper_bound( begin, prev, *it );
            shift(it, pos);
        }
}

template<typename Container>
	requires std::bidirectional_iterator<typename Container::iterator>
void binary_insertion_sort( Container& c )
{
	using std::begin;
	using std::end;
	binary_insertion_sort( begin(c), end(c) );
}
} // namespace aw
#endif // aw_algorithm_binary_insertion_sort_h
