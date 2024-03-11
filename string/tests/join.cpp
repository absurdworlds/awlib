#include <aw/utility/string/join.h>
#include <aw/test/test.h>
#include <aw/types/array_view.h>

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
	array_view<string_view> av = v;

	std::string s1;
	std::string s2;
	std::string s3;

	Setup {}
	Preconditions { }

	Checks {
		s1 = string::join(v);
		s2 = string::join(v);
		s3 = string::join(v, ", ");
	}

	Postconditions {
		TestEqual(s1, "Abcd?");
		TestEqual(s1, s2);
		TestEqual(s3, "A, b, c, d?");

		TestEqual(v.size(), 4);
	}
}

Test(concatenate) {
	using namespace std::string_literals;
	using namespace std::string_view_literals;
	auto str = string::concatenate("123", "456"sv, "789"s);
	Postconditions {
		TestEqual(str, "123456789");
	}
}

Test(reserve_string) {
	std::vector<string_view> v{ "AAA", "BBB", "CCCCC", "DDDD" };

	std::string s1 = string::reserve_string(begin(v), end(v));
	std::string s2 = string::reserve_string(begin(v), end(v), 1);

	TestAssert(s1.capacity() >= 15);
	TestAssert(s2.capacity() >= 18);
}
} // namespace aw
