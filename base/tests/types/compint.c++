#include <aw/types/composite_int.h>
#include <aw/string/to_string/composite_int.h>
#include <aw/test/test.h>
#include <limits>
#include <string>

TestFile( "aw::composite_int" );

namespace aw {
namespace {
using s_u64 = aw::composite_int<aw::u32>;
using s_i64 = aw::composite_int<aw::i32>;

s_u64 to_s(u64 v) { return { u32(v >> 32), u32(v) }; }
s_i64 to_s(i64 v) { return { i32(v >> 32), u32(v) }; }

u64 to_i(s_u64 v) { return     v.low() | (u64(v.high()) << 32); }
i64 to_i(s_i64 v) { return i64(v.low() | (u64(v.high()) << 32)); }

void CUEqual(s_u64 c, u64 u)
{
	TestEqual(to_i(c),     u);
	TestEqual(     c, to_s(u));
}

void CIEqual(s_i64 c, i64 i)
{
	TestEqual(to_i(c),     i);
	TestEqual(     c, to_s(i));
}

void CUPrints(u64 u)
{
	TestEqual(to_string(to_s(u), formatter::pretty_print{}), std::to_string(u));
}

void CIPrints(i64 i)
{
	TestEqual(to_string(to_s(i), formatter::pretty_print{}), std::to_string(i));
}

void unsigned_binary(u64 a, u64 b)
{
	const s_u64 c1 = to_s(a);
	const s_u64 c2 = to_s(b);

	CUEqual(c1 + c2, a + b);
	CUEqual(c1 - c2, a - b);
	CUEqual(c2 - c1, b - a);
	CUEqual(c1 * c2, a * b);
	CUEqual(c1 / c2, a / b);
	CUEqual(c2 / c1, b / a);

	TestEqual(c1 + c2, c2 + c1);
	TestEqual(c1 * c2, c2 * c1);
}

void unsigned_unary(u64 a)
{
	const s_u64 c = to_s(a);

	CUEqual(-c, -a);
	CUEqual(-c, -a);
}
} // namespace

Test(unsigned_arithmetic) {
	const u64 uval1 = 0x0000'0002'0000'1000;
	const u64 uval2 = 0x0000'0000'0100'2000;

	unsigned_binary(uval1, uval2);
	unsigned_binary(7777, 135487);
	unsigned_binary(898454457777, 135487);
	unsigned_binary(898454457777, 32947298479127);
	unsigned_unary(uval1);
	unsigned_unary(uval2);
	unsigned_unary(8788465464654654);
}

namespace {
void signed_binary(i64 a, i64 b)
{
	const s_i64 c1 = to_s(a);
	const s_i64 c2 = to_s(b);

	CIEqual(c1 + c2, a + b);
	CIEqual(c1 - c2, a - b);
	CIEqual(c2 - c1, b - a);
	CIEqual(c1 * c2, a * b);
	CIEqual(c1 / c2, a / b);
	CIEqual(c2 / c1, b / a);

	TestEqual(c1 + c2, c2 + c1);
	TestEqual(c1 * c2, c2 * c1);
}

void signed_unary(i64 a)
{
	const s_i64 c = to_s(a);

	CIEqual(-c, -a);
	CIEqual(-c, -a);
}
} // namespace

Test(signed_arithmetic) {
	static const i64 ival1 = -0x0000'0002'0000'1000;
	static const i64 ival2 = 0x0000'0000'0100'2000;

	signed_binary(ival1, ival2);
	signed_unary(ival1);
	signed_unary(ival2);
}

/*!
 * Shifting by the whole width or more leaves nothing behind.
 */
Test(compint_shift_by_whole_width) {
	constexpr size_t width = s_u64::digits;

	CUEqual(to_s(u64(0xdeadbeefcafef00d)) <<= width,     0);
	CUEqual(to_s(u64(0xdeadbeefcafef00d)) >>= width,     0);
	CUEqual(to_s(u64(0xdeadbeefcafef00d)) <<= width + 1, 0);
	CUEqual(to_s(u64(0xdeadbeefcafef00d)) >>= width + 1, 0);

	// the boundary just below is still a real shift
	CUEqual(to_s(u64(1)) <<= width - 1, u64(1) << (width - 1));
	CUEqual(to_s(u64(1) << (width - 1)) >>= width - 1, 1);

	// and the same for negative values
	CIEqual(to_s(i64(-1)) <<= width, 0);
	CIEqual(to_s(i64(-1)) >>= width, 0);
	CIEqual(to_s(i64(0x0123'4567'89ab'cdef)) <<= width, 0);
	CIEqual(to_s(i64(0x0123'4567'89ab'cdef)) >>= width, 0);
}

/*!
 * A composite prints as the number it represents
 */
Test(compint_to_string) {
	CUPrints(0);
	CUPrints(1);
	CUPrints(9);
	CUPrints(135487);
	CUPrints(0x0000'0002'0000'1000);
	CUPrints(~u64(0));

	CIPrints(0);
	CIPrints(1);
	CIPrints(-1);
	CIPrints(-135487);
	CIPrints(std::numeric_limits<i64>::max());
	CIPrints(std::numeric_limits<i64>::min());
}

/*!
 * sign() is -1, 0 or 1 for the whole value, including values
 * that fit entirely in the low half
 */
Test(compint_sign) {
	TestEqual(to_s(u64(0)).sign(),                     0u);
	TestEqual(to_s(u64(5)).sign(),                     1u);
	TestEqual(to_s(u64(0x0000'0001'0000'0000)).sign(), 1u);
	TestEqual(to_s(~u64(0)).sign(),                    1u);

	TestEqual(to_s(i64(0)).sign(),                       0);
	TestEqual(to_s(i64(5)).sign(),                       1);
	TestEqual(to_s(i64(0x0000'0001'0000'0000)).sign(),   1);
	TestEqual(to_s(i64(-1)).sign(),                     -1);
	TestEqual(to_s(i64(-0x0000'0001'0000'0000)).sign(), -1);
}

/*!
 * !x is true only for zero
 */
Test(compint_not) {
	TestAssert(!to_s(u64(0)));
	TestAssert(!!to_s(u64(5)));
	TestAssert(!!to_s(u64(0x0000'0001'0000'0000)));
	TestAssert(!!to_s(u64(0x0000'0001'0000'0005)));

	TestAssert(!to_s(i64(0)));
	TestAssert(!!to_s(i64(-1)));
	TestAssert(!!to_s(i64(5)));
}

// make_composite_int(hi, lo) is deprecated, but it is still tested until it's removed
#if defined(_MSC_VER) && !defined(__clang__)
#pragma warning(push)
#pragma warning(disable: 4996)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
/*!
 * make_composite_int(hi, lo) takes a sign and magnitude, the sign of hi
 * applies to the whole value, and the magnitude is |hi|·2ⁿ + lo
 */
Test(compint_make_deprecated) {
	CIEqual(make_composite_int<i32>(    3, 7u),     0x3'0000'0007);
	CIEqual(make_composite_int<i32>(   -1, 0u),    -0x1'0000'0000);
	CIEqual(make_composite_int<i32>(   -1, 1u),    -0x1'0000'0001);
	CIEqual(make_composite_int<i32>(-0x10, 0xFFu), -0x10'0000'00FF);
}
#if defined(_MSC_VER) && !defined(__clang__)
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif

/*!
 * make_composite_int(negative, hi, lo) is ±(hi·2ⁿ + lo) across the whole range
 */
Test(compint_make) {
	CIEqual(make_composite_int<i32>(false, 3,    7),     0x3'0000'0007);
	CIEqual(make_composite_int<i32>(true,  1,    0),    -0x1'0000'0000);
	CIEqual(make_composite_int<i32>(true,  1,    1),    -0x1'0000'0001);
	CIEqual(make_composite_int<i32>(true,  0x10, 0xFF), -0x10'0000'00FF);
	CIEqual(make_composite_int<i32>(true,  0,    0xFF), -0xFF);
	CIEqual(make_composite_int<i32>(true,  0,    0),     0);
	CIEqual(make_composite_int<i32>(true,  0x8000'0000, 0), std::numeric_limits<i64>::min());
	CIEqual(make_composite_int<i32>(false, 0x7FFF'FFFF, 0xFFFF'FFFF), std::numeric_limits<i64>::max());

	CUEqual(make_composite_int<u32>(false, 0x10, 0xFF), 0x10'0000'00FF);
	CUEqual(make_composite_int<u32>(false, 0xFFFF'FFFF, 0xFFFF'FFFF), ~u64(0));

	// usable in constant expressions
	static_assert(make_composite_int<i32>(true, 0, 1).high() == -1);
	static_assert(make_composite_int<i32>(true, 0, 1).low()  == 0xFFFF'FFFF);
}
} // namespace aw
