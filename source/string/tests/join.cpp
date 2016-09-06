#include <aw/utility/string/join.h>
#include <aw/utility/test.h>

TestFile( "string::join" );

namespace aw {
Test(join_empty) {
	std::vector<std::string> v;

	std::string s1;
	std::string s2;

	Setup {}
	Preconditions {
		test::check<test::equal>(v.empty(), true);
		test::check<test::equal>(s1.empty(), true);
		test::check<test::equal>(s2.empty(), true);
	}

	Checks {
		s1 = string::join(v);
		s2 = string::join(v, "  ");
	}

	Postconditions {
		test::check<test::equal>(s1.empty(), true);
		test::check<test::equal>(s2.empty(), true);
	}
}

Test(join_word) {
	std::vector<std::string> v{ "word" };

	std::string s1;
	std::string s2;

	Setup {}
	Preconditions {
		test::check<test::equal>(v.size(), 1);
		test::check<test::equal>(v[0], "word");
		test::check<test::equal>(s1.empty(), true);
		test::check<test::equal>(s2.empty(), true);
	}

	Checks {
		s1 = string::join(v);
		s2 = string::join(v, "  ");
	}

	Postconditions {
		test::check<test::equal>(s1, "word");
		test::check<test::equal>(s2, "word");

		test::check<test::equal>(v.size(), 1);
		test::check<test::equal>(v[0] == "word", 1);
	}
}

Test(join_words) {
	std::vector<std::string> v{ "A", "b", "c", "d?" };

	std::string s1;
	std::string s2;

	Setup {}
	Preconditions {
		test::check<test::equal>(v.size(), 4);

		test::check<test::equal>(s1.empty(), true);
		test::check<test::equal>(s2.empty(), true);
	}

	Checks {
		s1 = string::join(v);
		s2 = string::join(v, ", ");
	}

	Postconditions {
		test::check<test::equal>(s1, "Abcd?");
		test::check<test::equal>(s2, "A, b, c, d?");

		test::check<test::equal>(v.size(), 4);
	}
}
} // namespace aw
