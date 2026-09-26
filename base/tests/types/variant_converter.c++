
#include <aw/test/test.h>

#include <aw/types/support/variant_converter.h>

#include <string>

TestFile( "aw::variant_converter" );

namespace aw {

Test(variant_converter_perfect_forwarding) {
	struct MoveMeOnly {
		MoveMeOnly(std::string&& s) : s(std::move(s)) {}
		std::string s;
	};

	struct CopyMeOnly {
		CopyMeOnly(std::string& s) : s(s) {}
		std::string s;
	};

	std::variant<std::string> sv("Test");

	std::variant<CopyMeOnly> v1 = variant_converter{sv};
	std::variant<MoveMeOnly> v2 = variant_converter{std::move(sv)};

	
#if 0 // should not compile
	std::variant<MoveMeOnly> v3 = variant_converter{sv};
	std::variant<CopyMeOnly> v4 = variant_converter{std::move(sv)};
#endif

	TestAssert(std::get_if<CopyMeOnly>(&v1)->s == "Test");
	TestAssert(std::get_if<MoveMeOnly>(&v2)->s == "Test");
}

Test(variant_converter_superset) {
	std::variant<int, float> v1 = 1;
	std::variant<int, float, double> v2 = variant_converter{v1};

	auto i = std::get_if<int>(&v2);

	TestAssert(i != nullptr);
	TestEqual(*i, 1);
}

Test(variant_converter_compatible_types) {
	std::variant<int, float> v1 = 1;
	std::variant<long long, double> v2 = variant_converter{v1};

	auto i = std::get_if<long long>(&v2);

	TestAssert(i != nullptr);
	TestEqual(*i, 1);
}

} // namespace aw

