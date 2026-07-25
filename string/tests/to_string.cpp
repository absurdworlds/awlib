#include <aw/utility/to_string/all.h>
//#include <aw/types/traits/basic_traits.h>

#include <aw/math/vector3d.h>

#include <memory>
#include <vector>
#include <list>

#include <aw/test/test.h>

TestFile("to_string tests");

namespace aw {
using namespace std::string_literals;

Test(to_string_stringly_types) {
	TestAssert(to_string("") == ""s);
	TestAssert(to_string("raw string") == "raw string"s);
	TestAssert(to_string({"raw \"string\""}) == R"({"raw \"string\""})"s);
	TestAssert(to_string("string"s) == "string"s);
	TestAssert(to_string(std::vector<int>{1,2,3,-1,100,15,22}) == "{1, 2, 3, -1, 100, 15, 22}"s);
	TestAssert(to_string((void*)0) == "0"s);
	TestAssert(to_string(nullptr) == "nullptr"s);
	TestAssert(to_string(optional<int>(100)) == "100"s);
	TestAssert(to_string(optional<int>()) == ""s);
	TestAssert(to_string(nullopt) == "nullopt"s);
}

Test(to_string_char_types) {
	TestEqual(to_string('x'), "x"s);

	// TODO: ideally they should be converted to utf-8 string
	TestEqual(to_string((char8_t)65), "65"s);
	TestEqual(to_string((char16_t)66), "66"s);
	TestEqual(to_string((char32_t)67), "67"s);
	TestEqual(to_string((wchar_t)68), "68"s);
}

Test(to_string_arithmetic) {
	TestAssert(to_string(true)  == "true"s);
	TestAssert(to_string(false) == "false"s);
	TestAssert(to_string(888)   == "888"s);
	TestAssert(to_string(-888)  == "-888"s);
	TestAssert(to_string(1000u) == "1000"s);
	TestAssert(to_string(200000000000000000l) == "200000000000000000"s);
	TestAssert(to_string(18000000000000000000ul) == "18000000000000000000"s);

	TestEqual(to_string((signed char)-128), "-128"s);
	TestEqual(to_string((unsigned char)255), "255"s);
	TestEqual(to_string((short)-32768), "-32768"s);
	TestEqual(to_string((unsigned short)65535), "65535"s);

	TestEqual(to_string(int8_t(-1)), "-1"s);
	TestEqual(to_string(uint8_t(200)), "200"s);
	TestEqual(to_string(int16_t(-1000)), "-1000"s);
	TestEqual(to_string(uint16_t(2000)), "2000"s);
	TestEqual(to_string(int32_t(-1000000)), "-1000000"s);
	TestEqual(to_string(uint32_t(2000000)), "2000000"s);
	TestEqual(to_string(int64_t(-1000000000000)), "-1000000000000"s);
	TestEqual(to_string(uint64_t(2000000000000)), "2000000000000"s);

	// no control over precision yet
	//TestAssert(to_string(1000000.0f) == "1000000.0"s);
	//TestAssert(to_string(1000000.0) == "1000000.0"s);
}

Test(to_string_pointers) {
	auto ptr = std::make_unique<std::string>("s");
	TestAssert(to_string(ptr) == to_string(ptr.get()));
}

Test(to_string_math_types) {
	math::vector3d<int> vec3 {};
	math::matrix<int,4,4> mat4 {};
	TestAssert(to_string(vec3) == "{0, 0, 0}"s);
	TestAssert(to_string(mat4) == "{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}"s);
}

Test(to_string_compound) {
	TestEqual(to_string(std::vector<bool>{true, false}), "{true, false}"s);
	TestAssert(to_string(std::pair{10, "abc"}) == R"({10, "abc"})"s);

	std::list<std::vector<std::string>> lst{{"set", "time", "h", "[m]"}, {"get", "time"}, {"print", "time"}, {"set", "var", "x", "=", "value"}, {"get", "var", "x"}};

	TestAssert(to_string(lst) == R"({{"set", "time", "h", "[m]"}, {"get", "time"}, {"print", "time"}, {"set", "var", "x", "=", "value"}, {"get", "var", "x"}})"s);

	std::list<bool> lst1{ true, true, true };
	std::list<optional<bool>> lst2{ true, true, true };
	std::list<math::vector3d<int>> lst3{ {1, 0, 0} };

	TestAssert(to_string(lst1) == "{true, true, true}"s);
	TestAssert(to_string(lst2) == "{true, true, true}"s);
	TestAssert(to_string(lst3) == "{{1, 0, 0}}"s);

	TestEqual(to_string(std::vector<uint8_t>{1, 2, 3}), "{1, 2, 3}"s);

	TestEqual(to_string(std::vector<char>{'a', '\''}), R"({'a', '\''})"s);

	auto tuple1 = std::tuple{ 10, "xyz", false };
	auto tuple2 = std::tuple{ optional<std::string>{"test"}, "123", "123" };
	TestAssert(to_string(tuple1) == R"({10, "xyz", false})");
	TestEqual(to_string(tuple2), R"({"test", "123", "123"})");
}
} // namespace aw
