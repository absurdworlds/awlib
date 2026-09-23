#include <aw/test/test.h>
#include <aw/math/units.h>

TestFile("math::units");

namespace aw::math {
namespace {
// Units that aren't ratios
struct unit_turn    { using type = unit_turn;    static constexpr double value = 1;   };
struct unit_degree  { using type = unit_degree;  static constexpr double value = 360; };
} // namespace

Test(units_convert) {
	using turn   = std::ratio<1>;
	using degree = std::ratio<360>;

	TestEqual(units::convert(1.0, turn{},      degree{}),      360.0);
	TestEqual(units::convert(1.0, turn{},      unit_degree{}), 360.0);
	TestEqual(units::convert(1.0, unit_turn{}, degree{}),      360.0);
	TestEqual(units::convert(1.0, unit_turn{}, unit_degree{}), 360.0);

	TestEqual(units::convert(180.0, degree{},      turn{}),      0.5);
	TestEqual(units::convert(180.0, degree{},      unit_turn{}), 0.5);
	TestEqual(units::convert(180.0, unit_degree{}, turn{}),      0.5);
	TestEqual(units::convert(180.0, unit_degree{}, unit_turn{}), 0.5);
}
} // namespace aw::math
