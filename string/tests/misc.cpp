#include <aw/utility/string/join.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/trim.h>
#include <aw/test/test.h>
#include <cctype>

TestFile("Combined tests");

namespace aw {
Test(trim) {
	std::string str{" \t  a - b - c \t  "};
	std::string str1{str};
	std::string str2{str};
	std::string str3{str};
	std::string str4{str};
	std::string str5{str};

	std::string str_left{"a - b - c \t  "};
	std::string str_right{" \t  a - b - c"};
	std::string str_both{"a - b - c"};

	using namespace string;

	auto pred = [] (char c) {
		return std::isspace(c);
	};

	Checks {
		TestEqual(ltrimmed(str, pred), str_left);
		TestEqual(rtrimmed(str, pred), str_right);
		TestEqual(trimmed(str, pred), str_both);

		ltrim(str1, pred);
		rtrim(str2, pred);
		trim(str3, pred);
		ltrim(rtrim(str4, pred), pred);
		rtrim(ltrim(str5, pred), pred);
	}

	Postconditions {
		TestEqual(str1, str_left);
		TestEqual(str2, str_right);
		TestEqual(str3, str_both);
		TestEqual(str4, str3);
		TestEqual(str4, str5);
		TestEqual(str, " \t  a - b - c \t  ");
	}
};

Test(trim_string_view) {
	string_view str = ".str.";

	using namespace string;

	auto pred = [] (char c) {
		return c == '.';
	};

	Checks {
		TestEqual(trim_if(str, pred), "str");
		TestEqual(ltrim_if(str, pred), "str.");
		TestEqual(rtrim_if(str, pred), ".str");
	}
};

Test(split_and_join) {
	std::string s = "word1 word2 word3";
	std::vector<string_view> v;
	std::string r;

	Setup {
		v = string::split_by(s, " ");
	}

	Preconditions {
		std::vector<string_view> e{"word1", "word2", "word3"};
		TestAssert(v == e);
	}

	Checks {
		r = string::join(v, " ");
	}

	Postconditions {
		TestEqual(r, s);
	}
}

Test(join_and_split) {
	std::string s;
	std::vector<string_view> v{"word1", "word2", "word3"};
	std::vector<string_view> r;

	Setup {
		s = string::join(v, ", ");
	}

	Preconditions {
		TestEqual(s, "word1, word2, word3");
	}

	Checks {
		r = string::split_by(s, ", ");
	}

	Postconditions {
		TestAssert(r == v);
	}
}

Test(join_and_split2) {
	std::string s;
	std::vector<string_view> v{"word1", "word2", "word3"};
	std::vector<string_view> r;

	Setup {
		s = string::join(v, ", ");
	}

	Preconditions {
		TestEqual(s, "word1, word2, word3");
	}

	Checks {
		r = string::split(s, ", ");
	}

	Postconditions {
		TestAssert(r == v);
	}
}
} // namespace aw
