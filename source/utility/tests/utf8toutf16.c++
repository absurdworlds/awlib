#include <aw/utility/unicode/convert.h>
#include <aw/utility/test.h>

TestFile( "utf8toutf16" );

namespace aw {
Test(utf8toutf16)
{
	std::string    utf8 = u8"I am an unicode string å — °o АБВ αβγ Δ";
	std::u16string utf16 = u"I am an unicode string å — °o АБВ αβγ Δ";

	auto utf16_a = unicode::convert<std::u16string>(utf8);
	auto utf8_b  = unicode::convert<std::string>(utf16);

	auto utf8_a  = unicode::convert<std::string>(utf16_a);
	auto utf16_b = unicode::convert<std::u16string>(utf8_b);

	TestEqualV(utf8, utf8_a, utf8_b);
	TestEqualV(utf16, utf16_a, utf16_b);

}

Test(wstring)
{
	std::string  utf8  = u8"I am an unicode string å — °o АБВ αβγ Δ";
	std::wstring wide = L"I am an unicode string å — °o АБВ αβγ Δ";

	std::wstring wide_a = unicode::widen(utf8);
	std::string  utf8_b = unicode::narrow(wide);

	std::string  utf8_a = unicode::narrow(wide_a);
	std::wstring wide_b = unicode::widen(utf8_b);

	TestEqualV(utf8, utf8_a, utf8_b);
	TestEqualV(wide, wide_a, wide_b);

}
} // namespace aw
