#include <aw/test/test.h>

#include <aw/types/support/variant_cast.h>
#include <aw/types/traits/is_variant.h>

#include <string>

TestFile( "aw::variant_cast" );

namespace aw {

static_assert(is_std_variant_v<std::variant<int,float>>);
static_assert(!is_std_variant_v<void>);

Test(variant_cast_perfect_forwarding) {
	struct MoveMeOnly {
		MoveMeOnly(std::string&& s) : s(std::move(s)) {}
		std::string s;
	};

	struct CopyMeOnly {
		CopyMeOnly(std::string& s) : s(s) {}
		std::string s;
	};

	std::variant<std::string> sv("Test");

	auto v1 = variant_cast<std::variant<CopyMeOnly>>(sv);
	auto v2 = variant_cast<std::variant<MoveMeOnly>>(std::move(sv));

#if 0 // should not compile
	auto v3 = variant_cast<std::variant<MoveMeOnly>>(sv);
	auto v4 = variant_cast<std::variant<CopyMeOnly>>(std::move(sv));
#endif

	TestAssert(std::get_if<CopyMeOnly>(&v1)->s == "Test");
	TestAssert(std::get_if<MoveMeOnly>(&v2)->s == "Test");
}

Test(variant_cast_superset) {
	std::variant<int, float> v1 = 1;
	auto v2 = variant_cast<std::variant<int, float, double>>(v1);

	auto i = std::get_if<int>(&v2);

	TestAssert(i != nullptr);
	TestEqual(*i, 1);
}

Test(variant_cast_compatible_types) {
	std::variant<int, float> v1 = 1;
	auto v2 = variant_cast<std::variant<long long, double>>(v1);

	auto i = std::get_if<long long>(&v2);

	TestAssert(i != nullptr);
	TestEqual(*i, 1);
}

} // namespace aw

