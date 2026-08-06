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

Test(string_non_ascii_passes_through) {
	// bytes above 0x7f must reach should be
	// left alone in the C locale
	std::string s = "aÑb";
	std::string t = "AÑB";
	tolower(s);
	toupper(t);
	TestEqual(s, "aÑb");
	TestEqual(t, "AÑB");
	TestEqual(tolower("Ю"), "Ю");
	TestEqual(toupper("Ю"), "Ю");
}

} // namespace aw::string
