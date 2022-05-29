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
} // namespace aw
