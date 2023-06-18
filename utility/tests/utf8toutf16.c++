#include <aw/utility/unicode/convert.h>
#include <aw/test/test.h>

TestFile("utf8toutf16");

namespace aw {
Test(utf8toutf16)
{
	const std::pair<std::u8string, std::u16string> utf_strings[] = {
		{u8"I am an unicode string å — °o АБВ αβγ Δ", u"I am an unicode string å — °o АБВ αβγ Δ"},
		{u8"你好", u"你好"},
		{u8"こんにちは", u"こんにちは"},
		{u8"𠜎𠜱𠝹𠱓𠱸𠲖𠳏", u"𠜎𠜱𠝹𠱓𠱸𠲖𠳏"},
	};

	for (const auto& [utf8, utf16] : utf_strings) {
		auto utf16_a = unicode::convert<std::u16string>(utf8);
		auto utf8_a  = unicode::convert<std::u8string>(utf16);

		auto utf8_b  = unicode::convert<std::u8string>(utf16_a);
		auto utf16_b = unicode::convert<std::u16string>(utf8_a);

		TestEqualV(utf8, utf8_a, utf8_b);
		TestEqualV(utf16, utf16_a, utf16_b);
	}
}

Test(wstring)
{
	const std::pair<std::u8string, std::wstring> utf_strings[] = {
		{u8"I am an unicode string å — °o АБВ αβγ Δ", L"I am an unicode string å — °o АБВ αβγ Δ"},
		{u8"你好", L"你好"},
		{u8"こんにちは", L"こんにちは"},
		{u8"𠜎𠜱𠝹𠱓𠱸𠲖𠳏", L"𠜎𠜱𠝹𠱓𠱸𠲖𠳏"},
	};

	for (const auto& [utf8, wide] : utf_strings) {
		std::string narrow(begin(utf8), end(utf8));

		std::wstring wide_a   = unicode::widen(narrow);
		std::string  narrow_b = unicode::narrow(wide);

		std::string  narrow_a = unicode::narrow(wide_a);
		std::wstring wide_b   = unicode::widen(narrow_b);

		TestEqualV(narrow, narrow_a, narrow_b);
		TestEqualV(wide, wide_a, wide_b);
	}
}

Test(utf8toutf32)
{
	const std::pair<std::u8string, std::u32string> utf_strings[] = {
		{u8"I am an unicode string å — °o АБВ αβγ Δ", U"I am an unicode string å — °o АБВ αβγ Δ"},
		{u8"你好", U"你好"},
		{u8"こんにちは", U"こんにちは"},
		{u8"𠜎𠜱𠝹𠱓𠱸𠲖𠳏", U"𠜎𠜱𠝹𠱓𠱸𠲖𠳏"},
	};

	for (const auto& [utf8, utf32] : utf_strings) {
		auto utf32_a = unicode::convert<std::u32string>(utf8);
		auto utf8_b  = unicode::convert<std::u8string>(utf32);

		auto utf8_a  = unicode::convert<std::u8string>(utf32_a);
		auto utf32_b = unicode::convert<std::u32string>(utf8_b);

		TestEqualV(utf8, utf8_a, utf8_b);
		TestEqualV(utf32, utf32_a, utf32_b);
	}
}
Test(invalid_unicode_utf8_with_error)
{
	const std::string invalid_utf8_strings[] = {
		"\xC3\x30", // Invalid 2-byte sequence
		"\xF0\xBF\xC0\xBF" // Invalid 4-byte sequence
	};

	for (const auto& invalid_utf8 : invalid_utf8_strings) {
		bool error = false;
		auto utf32_a = unicode::convert<std::u32string>(invalid_utf8, error);

		TestAssert(error);
	}
}

Test(invalid_unicode_utf16_with_error)
{
	const std::u16string invalid_utf16_strings[] = {
		u"\xD800", // Unpaired high surrogate
		u"\xDC00" // Unpaired low surrogate
	};

	for (const auto& invalid_utf16 : invalid_utf16_strings) {
		bool error = false;
		auto utf32_a = unicode::convert<std::u32string>(invalid_utf16, error);

		TestAssert(error);
	}
}

} // namespace aw
