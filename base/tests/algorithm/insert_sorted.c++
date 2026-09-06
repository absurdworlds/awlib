#include <aw/algorithm/insert_sorted.h>
#include <aw/test/test.h>

#include <algorithm>
#include <vector>

TestFile( "algorithm::insert_sorted" );

namespace aw {
namespace {
//! carries its starting position, so equal elements can be told apart
struct tagged {
	int key;
	int tag;

	friend bool operator<(tagged a, tagged b) { return a.key < b.key; }
};

std::vector<int> tags(std::vector<tagged> const& v)
{
	std::vector<int> result;
	for (auto const& e : v)
		result.push_back(e.tag);
	return result;
}

//! ascending keys, each appearing twice, tagged by starting position
std::vector<tagged> run(int n)
{
	std::vector<tagged> v;
	for (int i = 0; i < n; ++i)
		v.push_back({ i / 2, i });
	return v;
}
} // namespace

//! The element preceeded by an empty range stays put
Test(insert_sorted_empty_range) {
	std::vector<int> vec{ 3, 1, 2 };

	insert_sorted(vec.begin(), vec.begin());

	Checks {
		TestEqual(vec, decltype(vec){ 3, 1, 2 });
	}
}

//! Element that's already in its place stays put
Test(insert_sorted_already_in_place) {
	std::vector<int> vec{ 1, 2, 3 };

	insert_sorted(vec.begin(), vec.begin() + 2);

	Checks {
		TestEqual(vec, decltype(vec){ 1, 2, 3 });
	}
}

//! An element preceding every other lands at the beginning
Test(insert_sorted_front) {
	std::vector<int> vec{ 2, 3, 4, 1 };

	insert_sorted(vec.begin(), vec.begin() + 3);

	Checks {
		TestEqual(vec, decltype(vec){ 1, 2, 3, 4 });
	}
}

//! ... and the elements it passes keep their order
Test(insert_sorted_middle) {
	std::vector<int> vec{ 1, 3, 4, 2 };

	insert_sorted(vec.begin(), vec.begin() + 3);

	Checks {
		TestEqual(vec, decltype(vec){ 1, 2, 3, 4 });
	}
}

//! Relative order of multiple equal elements is preverved
Test(insert_sorted_after_equals) {
	std::vector<tagged> vec{ {1,0}, {2,1}, {3,2}, {2,3} };

	insert_sorted(vec.begin(), vec.begin() + 3);

	Checks {
		TestEqual(tags(vec), std::vector<int>{ 0, 1, 3, 2 });
	}
}

//! The order matches a stable sort for any possible position
Test(insert_sorted_every_position) {
	Checks {
		for (int n = 1; n <= 6; ++n)
		for (int key = 0; key <= n; ++key) {
			auto vec = run(n);
			vec.push_back({ key, n });

			auto expected = vec;
			std::stable_sort(expected.begin(), expected.end());

			auto got = vec;
			insert_sorted(got.begin(), got.begin() + n);

			TestEqual(tags(got), tags(expected));
		}
	}
}

// same for the unguarded version
Test(insert_sorted_unguarded_every_position) {
	Checks {
		for (int n = 1; n <= 6; ++n)
		for (int key = 0; key <= n; ++key) {
			auto vec = run(n);
			vec.push_back({ key, n });

			auto expected = vec;
			std::stable_sort(expected.begin(), expected.end());

			auto got = vec;
			insert_sorted_unguarded(got.begin(), got.begin() + n);

			TestEqual(tags(got), tags(expected));
		}
	}
}
} // namespace aw
