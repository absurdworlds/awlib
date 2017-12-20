#include <aw/utility/ranges/zip.h>
#include <aw/utility/ranges/paired.h>
#include <aw/utility/test.h>
#include <numeric>

TestFile( "ranges::zip" );

namespace aw {
Test(pairs_test) {
	std::vector<int> vec1(15, 6);
	std::vector<size_t> vec2(15, 3);

	std::vector<int> result1;
	std::vector<size_t> result2;

	for (auto&& [first, second] : paired(vec1, vec2)) {
		result1.push_back(first);
		result2.push_back(second);
	}

	TestEqual(result1, vec1);
	TestEqual(result2, vec2);
}

Test(zip_test) {

	std::vector<int> vec1{1, 2, 3};
	std::vector<char> vec2{'a', 'b', 'c'};
	std::vector<float> vec3{1.0, 2.0, 3.0};

	std::vector<int> result1;
	std::vector<char> result2;
	std::vector<float> result3;

	for (auto&& [a,b,c] : zip(vec1, vec2, vec3)) {
		result1.push_back(a);
		result2.push_back(b);
		result3.push_back(c);
	}

	TestEqual(result1, vec1);
	TestEqual(result2, vec2);
	TestEqual(result3, vec3);
}
} // namespace aw
