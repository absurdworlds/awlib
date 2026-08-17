#include <aw/utility/ranges/slice.h>
#include <aw/test/test.h>

TestFile( "ranges::slice" );

namespace aw {
Test(slice_test) {
	std::vector<int> const vec {1,2,3,4,5,6,7,8,9};
	std::vector<int> vec2;
	std::vector<int> const expect {2,3,4,5,6,7,8};

	for (auto& val : aw::slice_range(vec, 1, 7))
		vec2.push_back(val);

	TestEqual(vec2, expect);
}

/*!
 * Storing the adapter outlives the temporary range, so it must
 * not produce dangling references.
 */
Test(slicing_a_temporary_keeps_it_alive) {
	auto slice = aw::slice_range(std::vector<int>{10, 20, 30, 40, 50}, 1, 3);

	std::vector<int> got;
	for (auto& val : slice)
		got.push_back(val);

	std::vector<int> const expect {20, 30, 40};
	TestEqual(got, expect);
}

/*!
 * Slicing an lvalue should not produce a copy.
 */
Test(lvalue_is_sliced_by_reference) {
	std::vector<int> vec{10, 20, 30, 40, 50};
	auto slice = aw::slice_range(vec, 1, 3);

	for (auto& val : slice)
		val += 1;

	std::vector<int> const expect {10, 21, 31, 41, 50};
	TestEqual(vec, expect);
}
} // namespace aw
