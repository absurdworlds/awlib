#include <aw/utility/ranges/ipairs.h>
#include <aw/test/test.h>
#include <numeric>

TestFile( "ranges::ipairs" );

namespace aw {
Test(ipairs_test) {
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
} // namespace aw
