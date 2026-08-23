#include <aw/types/composite_int.h>
#include <aw/string/to_string/composite_int.h>
#include <aw/test/test.h>
#include <limits>
#include <string>

TestFile( "aw::composite_int" );

namespace aw {
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
} // namespace aw
