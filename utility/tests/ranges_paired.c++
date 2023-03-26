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
} // namespace aw
