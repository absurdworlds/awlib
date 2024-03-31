#include <aw/utility/string/split.h>
#include <aw/test/test.h>

TestFile( "string::split" );

namespace aw {
Test(split_empty) {
	std::string s;

	std::vector<string_view> v1;
	std::vector<string_view> v2;

	Checks {
		v1 = string::split_by(s, "abcd");
		v2 = string::split(s, " ", string::keep_empty);
	}

	Postconditions {
		TestAssert(v1.empty());
		TestEqual(v2[0], "");
	}
}

Test(split_char) {
	std::string s = "a bc  d e ";

	std::vector<string_view> v1;
	std::vector<string_view> v2;

	Checks {
		v1 = string::split(s, ' ', string::discard_empty);
		v2 = string::split(s, ' ', string::keep_empty);
	}

	Postconditions {
		using V = std::vector<string_view>;
		TestEqual(v1, V{ "a", "bc", "d", "e" });
		TestEqual(v2, V{ "a", "bc", "", "d", "e", "" });
	}
}

Test(split_word) {
	std::string s = "word";

	std::vector<string_view> v1;
	std::vector<string_view> v2;

	Checks {
		v1 = string::split_by(s, " ");
		v2 = string::split(s, " ", string::keep_empty);
	}

	Postconditions {
		std::vector<string_view> expected{"word"};
		TestAssert(v1 == expected);
		TestAssert(v2 == expected);
	}
}

Test(split_words) {
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
		std::vector<string_view> e1{"word1", "word2", "word3"};
		std::vector<string_view> e2{"word1", "", "word2,", "word3"};
		std::vector<string_view> e3{"word1  word2", "word3"};
		TestEqual(v1, e1);
		TestEqual(v2, e2);
		TestEqual(v3, e3);
	}
}

Test(split_default) {
	std::string s = " a bc  d e ";

	std::vector<string_view> v1;
	std::vector<string_view> v2;

	Checks {
		v1 = string::split(s, ' ');
		v2 = string::split(s, ' ', string::discard_empty);
	}

	Postconditions {
		TestEqual(v1, v2);
	}
}
} // namespace aw
