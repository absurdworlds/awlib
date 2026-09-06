#include <algorithm>

#include "sort_tests.h"

TestFile( "algorithm::sort_control_tests" );

namespace aw {
using test_sort::unstable;

// control tests, for verifying the test harness itself:
// if any of these fail, it means the tests are wrong
TestSortAlgorithm(std_stable_sort,
	[](auto& v) { std::stable_sort(v.begin(), v.end()); })

TestSortAlgorithm(std_sort,
	[](auto& v) { std::sort(v.begin(), v.end()); }, unstable)

} // namespace aw
