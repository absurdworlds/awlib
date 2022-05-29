#include <aw/utility/unicode/convert.h>
#include <aw/test/test.h>

TestFile( "utf8toutf16" );

namespace aw {
Test(utf8toutf16)
{
	const std::u8string  utf8  = u8"I am an unicode string å — °o АБВ αβγ Δ";
	const std::u16string utf16 = u"I am an unicode string å — °o АБВ αβγ Δ";

	auto utf16_a = unicode::convert<std::u16string>(utf8);
	auto utf8_b  = unicode::convert<std::u8string>(utf16);

	auto utf8_a  = unicode::convert<std::u8string>(utf16_a);
	auto utf16_b = unicode::convert<std::u16string>(utf8_b);

	TestEqualV(utf8, utf8_a, utf8_b);
	TestEqualV(utf16, utf16_a, utf16_b);
}

Test(wstring)
{
	const std::u8string utf8 = u8"I am an unicode string å — °o АБВ αβγ Δ";

	std::string  narrow(begin(utf8), end(utf8));
	std::wstring wide = L"I am an unicode string å — °o АБВ αβγ Δ";

	std::wstring wide_a   = unicode::widen(narrow);
	std::string  narrow_b = unicode::narrow(wide);

	std::string  narrow_a = unicode::narrow(wide_a);
	std::wstring wide_b   = unicode::widen(narrow_b);

	TestEqualV(narrow, narrow_a, narrow_b);
	TestEqualV(wide, wide_a, wide_b);
}
} // namespace aw
