#include <aw/algorithm/binary_find.h>
#include <aw/test/test.h>
#include <functional>
#include <vector>

TestFile( "algorithm::binary_find" );

namespace aw {
Test(binary_find_present) {
	std::vector<int> v {1, 3, 5, 7};

	auto it = binary_find(begin(v), end(v), 5);
	TestAssert(it != end(v));
	TestEqual(*it, 5);
}

Test(binary_find_absent_between_elements) {
	std::vector<int> v {1, 3, 5, 7};

	auto it = binary_find(begin(v), end(v), 4);
	TestAssert(it == end(v));
}

Test(binary_find_absent_past_end) {
	std::vector<int> v {1, 3, 5, 7};

	auto it = binary_find(begin(v), end(v), 8);
	TestAssert(it == end(v));
}

Test(binary_find_empty_range) {
	std::vector<int> v;

	auto it = binary_find(begin(v), end(v), 1);
	TestAssert(it == end(v));
}

Test(binary_find_with_comparator) {
	std::vector<int> v {7, 5, 3, 1};

	auto it = binary_find(begin(v), end(v), 5, std::greater<int>{});
	TestAssert(it != end(v));
	TestEqual(*it, 5);

	auto miss = binary_find(begin(v), end(v), 4, std::greater<int>{});
	TestAssert(miss == end(v));
}
} // namespace aw
