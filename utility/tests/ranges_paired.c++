#include <aw/utility/ranges/paired.h>
#include <aw/test/test.h>
#include <numeric>

TestFile( "ranges::pairs" );

namespace aw {
Test(paired_test) {
	std::vector<int> vec1(15, 6);
	std::vector<size_t> vec2(15, 3);

	std::vector<int> result1;
	std::vector<size_t> result2;

	for (auto&& p : paired(vec1, vec2)) {
		result1.push_back(p.first);
		result2.push_back(p.second);
	}

	TestEqual(result1, vec1);
	TestEqual(result2, vec2);
}

Test(paired_ref) {
	std::vector<int> vec1{ 1, 2, 3, 4, 5, 6, 7 };
	std::vector<size_t> vec2(vec1.size());

	for (auto [v1, v2] : paired(vec1, vec2)) {
		v2 = static_cast<size_t>(v1) | 0x1;
	}

	const std::vector<size_t> expected({ 1, 3, 3, 5, 5, 7, 7 });
	TestEqual(vec2, expected);
}

Test(paired_rvalue) {
	std::vector<size_t> vec2(10, 0);

	for (auto [v1, v2] : paired(std::vector<int>{ 1, 2, 3, 4, 5, 6, 7 }, vec2)) {
		v2 = static_cast<size_t>(v1) | 0x1;
	}

	const std::vector<size_t> expected({ 1, 3, 3, 5, 5, 7, 7, 0, 0, 0 });
	TestEqual(vec2, expected);
}
} // namespace aw
