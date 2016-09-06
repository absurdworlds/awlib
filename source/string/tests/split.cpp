#include <aw/utility/string/split.h>
#include <aw/utility/test.h>

TestFile( "string::join" );

namespace aw {
Test(split_empty) {
	std::string s;

	std::vector<std::string> v1;
	std::vector<std::string> v2;

	Checks {
		v1 = string::split(s, "abcd");
		v2 = string::explode(s, " ");
	}

	Postconditions {
		TestAssert(v1.empty());
		TestEqual(v2[0], "");
	}
}

Test(split_word) {
	std::string s = "word";

	std::vector<std::string> v1;
	std::vector<std::string> v2;

	Checks {
		v1 = string::split(s, " ");
		v2 = string::explode(s, " ");
	}

	Postconditions {
		std::vector<std::string> expected{"word"};
		TestAssert(v1 == expected);
		TestAssert(v2 == expected);
	}
}

Test(split_words) {
	std::string s = "word1  word2, word3";

	std::vector<std::string> v1;
	std::vector<std::string> v2;
	std::vector<std::string> v3;

	Checks {
		v1 = string::split(s, ", ");
		v2 = string::explode(s, " ");
		v3 = string::explode(s, ", ");
	}

	Postconditions {
		std::vector<std::string> e1{"word1", "word2", "word3"};
		TestAssert(v1 == e1);
		std::vector<std::string> e2{"word1", "", "word2,", "word3"};
		TestAssert(v2 == e2);
		std::vector<std::string> e3{"word1  word2", "word3"};
		TestAssert(v3 == e3);
	}
}
} // namespace aw
