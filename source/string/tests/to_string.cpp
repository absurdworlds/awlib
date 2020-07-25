#include <aw/utility/to_string/all.h>
//#include <aw/types/traits/basic_traits.h>

#include <aw/math/vector3d.h>

#include <vector>
#include <list>

#include <aw/utility/test.h>

TestFile("to_string tests");

namespace aw {

Test(to_string) {
	using namespace std::string_literals;
	Checks {
		TestEqual(to_string(""), "");
		TestAssert(to_string("raw string") == "raw string"s);
		TestAssert(to_string({"raw \"string\""}) == R"({"raw \"string\""})"s);
		TestAssert(to_string("string"s) == "string"s);
		TestAssert(to_string(std::vector<int>{1,2,3,-1,100,15,22}) == "{1, 2, 3, -1, 100, 15, 22}"s);
		TestAssert(to_string((void*)0) == "0"s);
		TestAssert(to_string(nullptr) == "nullptr"s);
		TestAssert(to_string(optional<int>(100)) == "100"s);
		TestAssert(to_string(optional<int>()) == ""s);
		TestAssert(to_string(nullopt) == "nullopt"s);

		//TestAssert(to_string(std::make_unique<std::string>("s")));
		//
		TestAssert(to_string(true)  == "true"s);
		TestAssert(to_string(false) == "false"s);
		TestAssert(to_string(888)   == "888"s);
		TestAssert(to_string(-888)  == "-888"s);
		TestAssert(to_string(1000u) == "1000"s);
		TestAssert(to_string(200000000000000000l) == "200000000000000000"s);
		TestAssert(to_string(18000000000000000000ul) == "18000000000000000000"s);
		TestAssert(to_string(std::pair{10, "abc"}) == R"({10, "abc"})"s);
		// no control over precision yet
		//TestAssert(to_string(1000000.0f) == "1000000.0"s);
		//TestAssert(to_string(1000000.0) == "1000000.0"s);

		std::list<std::vector<std::string>> lst{{"set", "time", "h", "[m]"}, {"get", "time"}, {"print", "time"}, {"set", "var", "x", "=", "value"}, {"get", "var", "x"}};

		TestAssert(to_string(lst) == R"({{"set", "time", "h", "[m]"}, {"get", "time"}, {"print", "time"}, {"set", "var", "x", "=", "value"}, {"get", "var", "x"}})"s);

		std::list<bool> lst1{ true, true, true };
		std::list<optional<bool>> lst2{ true, true, true };
		std::list<math::vector3d<int>> lst3{ {1, 0, 0} };
		math::vector3d<int> vec3 {};
		math::matrix<int,4,4> mat4 {};


		TestAssert(to_string(lst1) == "{true, true, true}"s);
		TestAssert(to_string(lst2) == "{true, true, true}"s);
		TestAssert(to_string(lst3) == "{{1, 0, 0}}"s);
		TestAssert(to_string(vec3) == "{0, 0, 0}"s);
		TestAssert(to_string(mat4) == "{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}"s);

		auto tuple1 = std::tuple{ 10, "xyz", false };
		auto tuple2 = std::tuple{ optional<std::string>{"test"}, "123", "123" };
		TestAssert(to_string(tuple1) == R"({10, "xyz", false})");
		TestEqual(to_string(tuple2), R"({"test", "123", "123"})");
	}

	Postconditions {
	}
}
} // namespace aw

RunTests();
