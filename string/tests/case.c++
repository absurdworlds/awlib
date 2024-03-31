#include <aw/utility/string/case.h>
#include <aw/test/test.h>

TestFile("string::case");

namespace aw::string {

Test(string_tolower) {
	std::string s = "ABcd";
	tolower(s);
	TestEqual(s, "abcd");
	TestEqual(tolower("ABC"), "abc");
}

Test(string_toupper) {
	std::string s = "ABcd";
	toupper(s);
	TestEqual(s, "ABCD");
	TestEqual(toupper("abc"), "ABC");
}

Test(string_capitalize) {
	std::string s1 = "abcd";
	std::string s2 = "ABCD";
	std::string s3 = "a";
	std::string s4;
	capitalize(s1);
	capitalize(s2);
	capitalize(s3);
	capitalize(s4);
	TestEqual(s1, "Abcd");
	TestEqual(s2, "Abcd");
	TestEqual(s3, "A");
	TestEqual(s4, "");
}

} // namespace aw::string
