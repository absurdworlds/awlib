#include <aw/algorithm/sort/insertion_sort.h>
#include <aw/algorithm/sort/binary_insertion_sort.h>

#include "sort_tests.h"

TestFile( "algorithm::insertion_sort" );

namespace aw {
using test_sort::unstable;

TestSortAlgorithm(insertion_sort,
	[](auto& v) { insertion_sort(v.begin(), v.end()); })

TestSortAlgorithm(insertion_sort_container,
	[](auto& v) { insertion_sort(v); })

TestSortAlgorithm(binary_insertion_sort,
	[](auto& v) { binary_insertion_sort(v.begin(), v.end()); })

TestSortAlgorithm(binary_insertion_sort_container,
	[](auto& v) { binary_insertion_sort(v); })
} // namespace aw
