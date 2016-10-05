#include "string_view"
#include <experimental/string_view>
namespace e = std::experimental;
namespace z = awstd;

#include <aw/utility/test.h>

TestFile("string_view");

Test(compare_with_std) {
	e::string_view sv1("/test/patho/");
	z::string_view sv2("/test/patho/");

	TestEqual(sv1.find('/'), sv2.find('/'));
	TestEqual(sv1.rfind('/'), sv2.rfind('/'));

	TestEqual(sv1.find('x'), sv2.find('x'));
	TestEqual(sv1.rfind('x'), sv2.rfind('x'));

	TestAssert(sv1.find('t') == sv2.find('t'));
	TestAssert(sv1.rfind('t') == sv2.rfind('t'));

	TestEqual(sv1.find('t'), sv2.find('t'));
	TestEqual(sv1.rfind('t'), sv2.rfind('t'));

	TestEqual(sv1.find("path"), sv2.find("path"));
	TestEqual(sv1.rfind("path"), sv2.rfind("path"));

	TestEqual(sv1.find("/te"), sv2.find("/te"));
	TestEqual(sv1.rfind("/te"), sv2.rfind("/te"));

	TestEqual(sv1.find("ho/"), sv2.find("ho/"));
	TestEqual(sv1.rfind("ho/"), sv2.rfind("ho/"));

	TestEqual(sv1.find(sv1), sv2.find(sv2));
	TestEqual(sv1.rfind(sv1), sv2.rfind(sv2));

	TestEqual(sv1.find(""), sv2.find(""));
	TestEqual(sv1.rfind(""), sv2.rfind(""));


	TestEqual(sv1.find_last_not_of("/"), sv2.find_last_not_of("/"));
	TestEqual(sv1.find_last_not_of("x"), sv2.find_last_not_of("x"));

	TestEqual(sv1.find_last_of("/"), sv2.find_last_of("/"));
	TestEqual(sv1.find_last_of("h"), sv2.find_last_of("h"));
	TestEqual(sv1.find_last_of("x"), sv2.find_last_of("x"));

	TestEqual(sv1.find_first_of("/"), sv2.find_first_of("/"));
	TestEqual(sv1.find_first_of("h"), sv2.find_first_of("h"));
	TestEqual(sv1.find_first_of("x"), sv2.find_first_of("x"));

	TestEqual(sv1.find_first_not_of("/"), sv2.find_first_not_of("/"));
	TestEqual(sv1.find_first_not_of("h"), sv2.find_first_not_of("h"));

	TestEqual(sv1.find_last_not_of("/xo"), sv2.find_last_not_of("/xo"));
	TestEqual(sv1.find_last_not_of("ao"), sv2.find_last_not_of("ao"));

	TestEqual(sv1.find_last_of("/h"), sv2.find_last_of("/h"));
	TestEqual(sv1.find_last_of("xb"), sv2.find_last_of("xb"));

	TestEqual(sv1.find_first_of("/hx"), sv2.find_first_of("/hx"));
	TestEqual(sv1.find_first_of("ohx"), sv2.find_first_of("ohx"));

	TestEqual(sv1.find_first_not_of("/te"), sv2.find_first_not_of("/te"));

	TestEqual(sv1.data(), sv2);
	TestEqual(sv1, sv2.data());

	TestEqual(std::string(sv1.substr(3,5)), std::string(sv2.substr(3,5)));
	TestEqual(std::string(sv1.substr(0)), std::string(sv2.substr(0)));
	TestEqual(std::string(sv1.substr(sv1.size())), std::string(sv2.substr(sv2.size())));
}

int main(int,char**)
{
	return aw::test::registry::run();
}
