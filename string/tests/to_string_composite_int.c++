#include <aw/string/to_string/composite_int.h>
#include <aw/test/test.h>
#include <limits>
#include <string>

TestFile( "to_string::composite_int" );

namespace aw {
namespace {
using wide = composite_int<u64>;

std::string str(wide val)
{
	return to_string(val, formatter::pretty_print{});
}

//! A 64-bit composite build from two 32-bit ints, so results can be checked against i64
using narrow_signed = composite_int<i32>;

std::string str(i64 val)
{
	narrow_signed const c{ i32(val >> 32), u32(val) };
	return to_string(c, formatter::pretty_print{});
}
} // namespace

/*!
 * A value which fits into a built-in integer reads the same
 * as the plain integer would.
 */
Test(composite_int_to_string_small_values)
{
	TestEqual(str(wide{0, 0}), std::string("0"));
	TestEqual(str(wide{0, 1}), std::string("1"));
	TestEqual(str(wide{0, 9}), std::string("9"));
	TestEqual(str(wide{0, 1234567890}), std::string("1234567890"));
}

/*!
 * A value too large for a built-in integer is spelled out in full.
 */
Test(composite_int_to_string_wide_values)
{
	// 2^64
	TestEqual(str(wide{1, 0}), std::string("18446744073709551616"));
	// 2^64 + 1
	TestEqual(str(wide{1, 1}), std::string("18446744073709551617"));
	// 2^128 - 1
	TestEqual(str(wide{~u64(0), ~u64(0)}),
	          std::string("340282366920938463463374607431768211455"));
}

/*!
 * A negative value is spelled with a sign, down to the most negative one (included).
 */
Test(composite_int_to_string_signed_values)
{
	TestEqual(str(i64(0)),  std::string("0"));
	TestEqual(str(i64(1)),  std::string("1"));
	TestEqual(str(i64(-1)), std::string("-1"));
	TestEqual(str(i64(-1234567890)), std::string("-1234567890"));

	constexpr auto max = std::numeric_limits<i64>::max();
	constexpr auto min = std::numeric_limits<i64>::min();
	TestEqual(str(max), std::to_string(max));
	TestEqual(str(min), std::to_string(min));
}
} // namespace aw
