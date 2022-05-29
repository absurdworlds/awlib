#include <aw/test/test.h>
#include <aw/math/angle.h>
#include <aw/math/trigonometry.h>

#include <algorithm>

TestFile("math::angle");

namespace aw {
namespace math {
Test(angle_conversion) {
	degrees<f32> d1{ 30 };
	radians<f32> r1{ pi/6 };

	degrees<f32> d2{ r1 };
	degrees<f32> d3{ 60 };
	degrees<f64> d4{ 30 };

	TestEqual(d1.count(), d2.count());
	TestEqual(d3.count(), (2*d1).count());
	TestEqual((d1*2).count(), (2*d1).count());
	TestEqual((d4+d1).count(), (d1+d1).count());

	TestAssert(d3 == (d1+r1));
	TestAssert( d1 < d3 );
	TestAssert( r1 <= d1 );
	TestAssert( d3 > d4 );
	TestAssert( d4 == d1 );
	TestAssert( equals(d4, r1) );
	TestAssert( d3 != d4 );
};

Test(angle_trigon) {
	TestAssert( equals( cos(degrees<f32>{ 0.0f }), 1.0f) );
	TestAssert( equals( sin(degrees<f32>{ 90.0f }), 1.0f) );
};

Test(angle_arithmetic) {
	constexpr degrees<int> a1{ 30 };
	constexpr degrees<int> a2{ 45 };

	constexpr radians<f64> b1 = a1;
	constexpr radians<f64> b2 = a2;

	constexpr degrees<int> a3 = a1 + a2 + a1/2;
	constexpr radians<f64> b3 = b1 + b2 + b1/2;
	TestEqual( a3.count(), 90 );
	TestAssert( equals( b3.count(), pi/2 ) );
}

Test(angle_normalize) {
	TestEqual( degrees<int>{ -181 }.normalize().count(), 179 );
	TestEqual( degrees<int>{ -180 }.normalize().count(), -180 );
	TestEqual( degrees<int>{ -90 }.normalize().count(),  -90 );
	TestEqual( degrees<int>{ 90 }.normalize().count(), 90 );
	TestEqual( degrees<int>{ 180 }.normalize().count(), -180 );
	TestEqual( degrees<int>{ 270 }.normalize().count(), -90 );
	TestEqual( degrees<int>{ 360 }.normalize().count(), 0 );
	TestEqual( degrees<int>{ 540 }.normalize().count(), -180 );

	TestEqual( degrees<float>{ -181.f }.normalize().count(), 179.f );
	TestEqual( degrees<float>{ 90.f }.normalize().count(), 90.f );
	TestEqual( degrees<float>{ -90.f }.normalize().count(), -90.f );
	TestEqual( degrees<float>{ 360.f }.normalize().count(), 0.f );
	TestEqual( degrees<float>{ 540.f }.normalize().count(), -180.f );
}
} // namespace math
} // namespace aw
