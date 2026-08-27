#include <aw/ranges/zip.h>
#include <aw/string/to_string/pair.h>
#include <aw/test/test.h>
#include <numeric>
#include <utility>

TestFile( "ranges::zip" );

namespace aw {
Test(pairs_test) {
	std::vector<int> vec1(15, 6);
	std::vector<size_t> vec2(15, 3);

	std::vector<int> result1;
	std::vector<size_t> result2;

	for (auto&& [first, second] : zip(vec1, vec2)) {
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

/*
 * Iteration stops after the shorter range, regardless of which
 * argument it is.
 */
Test(unequal_lengths_stop_at_the_shortest) {
	std::vector<int> shorter{1, 2};
	std::vector<int> longer {10, 20, 30, 40};

	std::vector<std::pair<int,int>> seen;
	for (auto&& [a, b] : zip(shorter, longer))
		seen.emplace_back(a, b);

	TestEqual(seen, (std::vector<std::pair<int,int>>{ {1,10}, {2,20} }));

	seen.clear();
	for (auto&& [a, b] : zip(longer, shorter))
		seen.emplace_back(a, b);

	TestEqual(seen, (std::vector<std::pair<int,int>>{ {10,1}, {20,2} }));
}
} // namespace aw
