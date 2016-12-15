#include <aw/utility/string/join.h>
#include <aw/utility/test.h>

TestFile( "string::join" );

namespace aw {
Test(join_empty) {
	std::vector<string_view> v;

	std::string s1;
	std::string s2;

	Checks {
		s1 = string::join(v);
		s2 = string::join(v, "  ");
	}

	Postconditions {
		TestAssert(s1.empty());
		TestAssert(s2.empty());
	}
}

Test(join_word) {
	std::vector<string_view> v{ "word" };

	std::string s1;
	std::string s2;

	Checks {
		s1 = string::join(v);
		s2 = string::join(v, "  ");
	}

	Postconditions {
		TestEqual(s1, "word");
		TestEqual(s2, "word");

		TestEqual(v.size(), 1);
		TestEqual(v[0], "word");
	}
}

Test(join_words) {
	std::vector<string_view> v{ "A", "b", "c", "d?" };

	std::string s1;
	std::string s2;

	Setup {}
	Preconditions { }

	Checks {
		s1 = string::join(v);
		s2 = string::join(v, ", ");
	}

	Postconditions {
		TestEqual(s1, "Abcd?");
		TestEqual(s2, "A, b, c, d?");

		TestEqual(v.size(), 4);
	}
}
} // namespace aw
