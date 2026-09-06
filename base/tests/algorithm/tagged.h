#ifndef aw_tests_algorithm_tagged_h
#define aw_tests_algorithm_tagged_h

#include <vector>

namespace aw::test_sort {
namespace {

//! Carries its starting position, so equal elements can be told apart
struct tagged {
	int key;
	int tag;

	friend bool operator<(tagged a, tagged b) { return a.key < b.key; }
};

//! Tag each key with a number corresponding to its posision
[[maybe_unused]] std::vector<tagged> tag(std::vector<int> const& k)
{
	std::vector<tagged> v;
	for (size_t i = 0; i < k.size(); ++i)
		v.push_back({ k[i], int(i) });
	return v;
}

//! Extracts tag from each element
[[maybe_unused]] std::vector<int> tags(std::vector<tagged> const& v)
{
	std::vector<int> result;
	for (auto const& e : v)
		result.push_back(e.tag);
	return result;
}

//! Strips tag from each element
[[maybe_unused]] std::vector<int> keys(std::vector<tagged> const& v)
{
	std::vector<int> result;
	for (auto const& e : v)
		result.push_back(e.key);
	return result;
}

} // namespace
} // namespace aw::test_sort

#endif // aw_tests_algorithm_tagged_h
