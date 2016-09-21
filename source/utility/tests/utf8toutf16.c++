#include <aw/utility/unicode/convert.h>
#include <aw/utility/test.h>

TestFile( "utf8toutf16" );

namespace aw {
Test(basic_utf)
{
	std::string    utf8 = u8"I am an unicode string å — °o АБВ αβγ Δ";
	std::u16string utf16 = u"I am an unicode string å — °o АБВ αβγ Δ";

	std::u16string utf16_a = unicode::widen(utf8);
	std::string    utf8_b  = unicode::narrow(utf16);

	std::string    utf8_a  = unicode::narrow(utf16_a);
	std::u16string utf16_b = unicode::widen(utf8_b);

	TestEqualV(utf8, utf8_a, utf8_b);
	TestEqualV(utf16, utf16_a, utf16_b);

}
} // namespace aw
