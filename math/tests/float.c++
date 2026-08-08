#include <aw/math/float.h>
#include <aw/math/equals.h>
#include <aw/test/test.h>

#include <cmath>
#include <limits>

TestFile("math::float");

namespace aw {
namespace math {
namespace {
//! Move \a value by \a steps ULPs, towards +inf for positive \a steps
template<typename F>
F step_ulps(F value, int steps)
{
	F dir = steps < 0 ? -std::numeric_limits<F>::infinity()
	                  :  std::numeric_limits<F>::infinity();
	for (int i = 0, n = std::abs(steps); i < n; ++i)
		value = std::nextafter(value, dir);
	return value;
}

/*
 * The comparisons fall back on an absolute epsilon (1e-4 for f32,
 * 1e-7 for f64), which swallows any ULP-sized difference around 1.0.
 * The values below are large enough that a single ULP exceeds that
 * epsilon, so only the ULP path can decide them.
 */
constexpr f32 big32 = 1e6f; // 1 ULP = 0.0625
constexpr f64 big64 = 1e12; // 1 ULP = 0.0001220703125
} // namespace

Test(step_ulps) {
	// the helper the rest of the tests rely on
	TestEqual( step_ulps(1.f, 0), 1.f );
	TestEqual( step_ulps(step_ulps(1.f, 1), -1), 1.f );
	TestEqual( step_ulps(1.f, 1), 1.f + std::numeric_limits<f32>::epsilon() );
	TestAssert( step_ulps(big32, 1) > big32 );
	TestAssert( step_ulps(big32, -1) < big32 );
};

Test(almost_equal_ulps) {
	Preconditions {
		// a single ULP must be outside the epsilon fallback,
		// otherwise these tests prove nothing about the ULP path
		TestAssert( step_ulps(big32, 1) - big32 > float_traits<f32>::epsilon );
		TestAssert( step_ulps(big64, 1) - big64 > float_traits<f64>::epsilon );
	}

	Checks {
		TestAssert(  aw::_impl::almost_equal_ulps(big32, big32, 4) );
		TestAssert(  aw::_impl::almost_equal_ulps(big32, step_ulps(big32, 1), 4) );
		TestAssert(  aw::_impl::almost_equal_ulps(big32, step_ulps(big32, 4), 4) );
		TestAssert( !aw::_impl::almost_equal_ulps(big32, step_ulps(big32, 5), 4) );
		TestAssert( !aw::_impl::almost_equal_ulps(big32, step_ulps(big32, 1000), 4) );
	}

	Checks {
		TestAssert(  aw::_impl::almost_equal_ulps(big64, big64, 8) );
		TestAssert(  aw::_impl::almost_equal_ulps(big64, step_ulps(big64, 8), 8) );
		TestAssert( !aw::_impl::almost_equal_ulps(big64, step_ulps(big64, 9), 8) );
	}

	// the argument order must not matter
	Checks {
		TestAssert(  aw::_impl::almost_equal_ulps(step_ulps(big32, 4), big32, 4) );
		TestAssert( !aw::_impl::almost_equal_ulps(step_ulps(big32, 5), big32, 4) );
		TestAssert(  aw::_impl::almost_equal_ulps(step_ulps(big32, -4), big32, 4) );
		TestAssert( !aw::_impl::almost_equal_ulps(step_ulps(big32, -5), big32, 4) );
	}

	// negative values are ordered the other way round in memory
	Checks {
		TestAssert(  aw::_impl::almost_equal_ulps(-big32, step_ulps(-big32, 4), 4) );
		TestAssert( !aw::_impl::almost_equal_ulps(-big32, step_ulps(-big32, 5), 4) );
		TestAssert(  aw::_impl::almost_equal_ulps(-big32, step_ulps(-big32, -4), 4) );
		TestAssert( !aw::_impl::almost_equal_ulps(-big32, step_ulps(-big32, -5), 4) );
	}

	// a zero tolerance still accepts identical values
	Checks {
		TestAssert(  aw::_impl::almost_equal_ulps(big32, big32, 0) );
		TestAssert( !aw::_impl::almost_equal_ulps(big32, step_ulps(big32, 1), 0) );
	}
};

Test(almost_equal_ulps_signs) {
	// values straddling zero are never within a few ULPs of each other
	TestAssert( !aw::_impl::almost_equal_ulps(1e-30f, -1e-30f, 4) );
	TestAssert( !aw::_impl::almost_equal_ulps(1.f, -1.f, 4) );
};

Test(almost_equal_ulps_signed_zero) {
	// both zeroes are the same number
	TestAssert( aw::_impl::almost_equal_ulps(0.f, -0.f, 4) );
	TestAssert( aw::_impl::almost_equal_ulps(0.0, -0.0, 8) );
};

Test(compare_ulps) {
	Checks {
		TestAssert(  compare_ulps(big32, big32) );
		TestAssert(  compare_ulps(big32, step_ulps(big32, 4)) );
		TestAssert( !compare_ulps(big32, step_ulps(big32, 64)) );
		TestAssert( !compare_ulps(big32, big32 * 2) );

		TestAssert(  compare_ulps(big64, big64) );
		TestAssert(  compare_ulps(big64, step_ulps(big64, 8)) );
		TestAssert( !compare_ulps(big64, step_ulps(big64, 128)) );
		TestAssert( !compare_ulps(big64, big64 * 2) );
	}

	// near zero the ULP spacing is meaningless and the epsilon takes over
	Checks {
		TestAssert(  compare_ulps(0.f, 1e-6f) );
		TestAssert(  compare_ulps(0.f, -1e-6f) );
		TestAssert( !compare_ulps(0.f, 1.f) );

		TestAssert(  compare_ulps(0.0, 1e-9) );
		TestAssert( !compare_ulps(0.0, 1.0) );
	}
};

Test(equals_float) {
	// equals() must tolerate an error proportional to the magnitude:
	// at 1e7 one ULP is a whole 1.0, far above the absolute epsilon
	f32 a = 1e7f;

	Preconditions {
		TestEqual( step_ulps(a, 1), a + 1.f );
	}

	Checks {
		TestAssert(  equals(a, a + 1.f) );
		TestAssert( !equals(a, a + 64.f) );

		TestAssert(  equals(big64, step_ulps(big64, 8)) );
		TestAssert( !equals(big64, step_ulps(big64, 9)) );
	}

	// and it must stay exact for integers, which are not compared as floats
	Checks {
		TestAssert(  equals(1000000, 1000000) );
		TestAssert( !equals(1000000, 1000001) );
	}
};
} // namespace math
} // namespace aw
