
#include <aw/test/test.h>

#include <aw/types/support/variant_converter.h>

#include <string>

TestFile( "aw::variant_converter" );

namespace aw {

Test(variant_converter_perfect_forwarding) {
	struct MoveMeOnly {
		MoveMeOnly(std::string&&) {}
	};

	struct CopyMeOnly {
		CopyMeOnly(std::string&) {}
	};

	std::variant<std::string> sv;

	std::variant<MoveMeOnly> v1 = variant_converter{std::move(sv)};
	std::variant<CopyMeOnly> v2 = variant_converter{sv};

	// should not compile
	//std::variant<MoveMeOnly> v3 = variant_converter{sv};
	//std::variant<CopyMeOnly> v4 = variant_converter{std::move(sv)};
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

