#include <aw/algorithm/insert_sorted.h>
#include <aw/ranges/value_range.h>
#include <aw/test/test.h>

#include "tagged.h"

#include <algorithm>
#include <vector>

TestFile( "algorithm::insert_sorted" );

namespace aw {
namespace {
using test_sort::tagged;
using test_sort::tags;

//! ascending keys, each appearing twice, tagged by starting position
std::vector<tagged> run(int n)
{
	std::vector<tagged> v;
	for (int i : range(n))
		v.push_back({ i / 2, i });
	return v;
}

//! inserts a key into a sorted run, for every key and every length of run
template<typename Insert>
void check_every_position(Insert insert)
{
	for (int n : range(1, 7))
	for (int key : range(n + 1)) {
		auto vec = run(n);
		vec.push_back({ key, n });

		auto expected = vec;
		std::stable_sort(expected.begin(), expected.end());

		auto got = vec;
		insert(got.begin(), got.begin() + n);

		TestEqual(tags(got), tags(expected));
	}
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
		check_every_position([](auto begin, auto pos) { insert_sorted(begin, pos); });
	}
}

// same for the unguarded version
Test(insert_sorted_unguarded_every_position) {
	Checks {
		check_every_position([](auto begin, auto pos) { insert_sorted_unguarded(begin, pos); });
	}
}
} // namespace aw
