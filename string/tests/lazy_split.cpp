#include <aw/utility/string/split.h>
#include <aw/utility/string/lazy_split.h>
#include <aw/test/test.h>

TestFile( "string::lazy_split" );

namespace aw {
Test(lazy_split_empty) {
	std::string s;

	Checks {
		auto v1 = string::split_by(s, "abcd");
		auto l1 = string::lazy::split_by(s, "abcd");
		auto v2 = string::split(s, " ", string::keep_empty);
		auto l2 = string::lazy::cut(s, " ");

		bool equal1 = std::equal( begin(v1), end(v1), begin(l1), end(l1) );
		bool equal2 = std::equal( begin(v2), end(v2), begin(l2), end(l2) );
		TestAssert( equal1 );
		TestAssert( equal2 );
	}
}

Test(lazy_split_word) {
	std::string s = "word";

	Postconditions {
		auto v1 = string::split_by(s, " ");
		auto l1 = string::lazy::split_by(s, " ");
		auto v2 = string::split(s, " ", string::keep_empty);
		auto l2 = string::lazy::cut(s, " ");

		bool equal1 = std::equal( begin(v1), end(v1), begin(l1), end(l1) );
		bool equal2 = std::equal( begin(v2), end(v2), begin(l2), end(l2) );
		TestAssert( equal1 );
		TestAssert( equal2 );
	}
}

Test(lazy_split_words) {
	std::string s = "word1  word2, word3";

	std::vector<string_view> v1;
	std::vector<string_view> v2;
	std::vector<string_view> v3;

	Checks {
		v1 = string::split_by(s, ", ");
		v2 = string::split(s, " ", string::keep_empty);
		v3 = string::split(s, ", ", string::keep_empty);
	}

	Postconditions {
		auto v1 = string::split_by(s, ", ");
		auto v2 = string::split(s, " ", string::keep_empty);
		auto v3 = string::split(s, ", ", string::keep_empty);
		auto l1 = string::lazy::split_by(s, ", ");
		auto l2 = string::lazy::cut(s, " ");
		auto l3 = string::lazy::cut(s, ", ");

		bool equal1 = std::equal( begin(v1), end(v1), begin(l1), end(l1) );
		bool equal2 = std::equal( begin(v2), end(v2), begin(l2), end(l2) );
		bool equal3 = std::equal( begin(v3), end(v3), begin(l3), end(l3) );
		TestAssert( equal1 );
		TestAssert( equal2 );
		TestAssert( equal3 );
	}
}
} // namespace aw
