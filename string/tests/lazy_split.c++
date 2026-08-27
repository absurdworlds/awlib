#include <aw/string/split.h>
#include <aw/string/lazy_split.h>
#include <aw/test/test.h>

TestFile( "string::lazy_split" );

namespace aw {
namespace {
//! Materialise a lazy split, so it can be compared to the eager one
std::vector<string_view> collect(auto lazy)
{
	std::vector<string_view> substrs;
	for (auto substr : lazy)
		substrs.push_back(substr);
	return substrs;
}

/*
 * Each lazy iterator is specified to produce exactly what its eager
 * counterpart produces, so every test here is the same test.
 */
void test_lazy(string_view source, string_view delim)
{
	using namespace string;
	TestEqual( collect(lazy::split_by(source, delim)), split_by(source, delim) );
	TestEqual( collect(lazy::cut(source, delim)),      split(source, delim, keep_empty) );
	TestEqual( collect(lazy::split(source, delim)),    split(source, delim, discard_empty) );
}
} // namespace

Test(lazy_split_empty_string) {
	Checks {
		test_lazy("", "abcd");
		test_lazy("", " ");
	}
}

Test(lazy_split_empty_delim) {
	Checks {
		test_lazy("abcdef", "");
		test_lazy("", "");
	}
}

Test(lazy_split_word) {
	Checks {
		test_lazy("word", " ");
	}
}

Test(lazy_split_words) {
	Checks {
		test_lazy("word1  word2, word3", " ");
		test_lazy("word1  word2, word3", ", ");
	}
}
} // namespace aw
