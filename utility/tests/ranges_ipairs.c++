#include <aw/utility/ranges/ipairs.h>
#include <aw/test/test.h>
#include <numeric>

TestFile( "ranges::ipairs" );

namespace aw {
Test(ipairs_basic_test) {
	std::vector<int> vec1(15, 0);
	std::vector<size_t> vec2(15, 0);
	std::iota(begin(vec2), end(vec2), 0);

	std::vector<int> result1;
	std::vector<size_t> result2;

	for (auto&& p : ipairs(vec1)) {
		result2.push_back(p.first);
		result1.push_back(p.second);
	}

	TestEqual(result1, vec1);
	TestEqual(result2, vec2);
}

/*!
 * Storing the adapter outlives the temporary range, so it must
 * not produce dangling references.
 */
Test(ipairs_keeps_a_temporary_alive) {
	auto pairs = ipairs(std::vector<int>{10, 20, 30, 40});

	std::vector<size_t> indices;
	std::vector<int>    values;
	for (auto&& p : pairs) {
		indices.push_back(p.first);
		values.push_back(p.second);
	}

	std::vector<size_t> const expect_idx {0, 1, 2, 3};
	std::vector<int>    const expect_val {10, 20, 30, 40};
	TestEqual(indices, expect_idx);
	TestEqual(values, expect_val);
}

/*!
 * An lvalue range is referred to, not copied, so writes through the
 * pair reach the original container.
 */
Test(ipairs_lvalue_kept_by_reference) {
	std::vector<int> vec{10, 20, 30, 40};
	auto pairs = ipairs(vec);

	for (auto&& p : pairs)
		p.second += 1;

	std::vector<int> const expect {11, 21, 31, 41};
	TestEqual(vec, expect);
}
} // namespace aw
