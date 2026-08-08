/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/C++98/utility/unicode/convert.h>

#include <string>
#include <vector>

#include "awstd_test.h"

namespace u = aw::unicode;

namespace {
u::code_point const code_points[] = {
	0x24,     // $, 1 byte in utf-8
	0x41,     // A
	0xA2,     // (cent sign), 2 bytes
	0x7FF,
	0x939,    // (devanagari ha), 3 bytes
	0x20AC,   // (euro sign)
	0xFFFD,
	0x10348,  // (gothic hwair), 4 bytes, a surrogate pair in utf-16
	0x10FFFF
};

size_t const code_point_count = sizeof(code_points) / sizeof(code_points[0]);

//! Encode the sample code points with \a Enc, then decode them back
template<typename Enc>
void test_roundtrip(std::string const& name)
{
	std::string const ctx = " [" + name + "]";

	typedef std::vector<typename Enc::char_type> buffer;

	buffer encoded;
	std::back_insert_iterator<buffer> out = std::back_inserter(encoded);
	for (size_t i = 0; i < code_point_count; ++i)
		out = Enc::encode(code_points[i], out);

	size_t count = 0;
	typename buffer::const_iterator begin = encoded.begin();
	typename buffer::const_iterator end   = encoded.end();
	while (begin != end) {
		u::code_point cp = u::invalid;
		begin = Enc::decode(begin, end, cp);

		if (count < code_point_count)
			CheckEqualCtx(cp, code_points[count], ctx);
		++count;
	}

	CheckEqualCtx(count, code_point_count, ctx);
}

void test_widths()
{
	CheckEqual(u::utf8::width(0x24),     size_t(1));
	CheckEqual(u::utf8::width(0xA2),     size_t(2));
	CheckEqual(u::utf8::width(0x939),    size_t(3));
	CheckEqual(u::utf8::width(0x10348),  size_t(4));
	CheckEqual(u::utf8::width(0x110000), size_t(0));

	CheckEqual(u::utf16::width(0x24),    size_t(1));
	CheckEqual(u::utf16::width(0x10348), size_t(2));

	Check(u::isValidCodepoint(0x10FFFF));
	Check(!u::isValidCodepoint(0x110000));
	Check(!u::isValidCodepoint(0xD800));
	Check(u::isSurrogate(0xDFFF));
	Check(!u::isSurrogate(0xE000));
}

void test_utf8_encoding()
{
	// a well-known encoding, to make sure the roundtrip is not
	// consistently wrong in both directions
	std::string encoded;
	std::back_insert_iterator<std::string> out = std::back_inserter(encoded);
	out = u::utf8::encode(0x20AC, out);

	CheckEqual(encoded.size(), size_t(3));
	CheckEqual(int(static_cast<unsigned char>(encoded[0])), 0xE2);
	CheckEqual(int(static_cast<unsigned char>(encoded[1])), 0x82);
	CheckEqual(int(static_cast<unsigned char>(encoded[2])), 0xAC);
}

void test_utf16_surrogates()
{
	typedef std::vector<u::utf16::char_type> buffer;

	buffer encoded;
	std::back_insert_iterator<buffer> out = std::back_inserter(encoded);
	out = u::utf16::encode(0x10348, out);

	CheckEqual(encoded.size(), size_t(2));
	CheckEqual(int(encoded[0]), 0xD800);
	CheckEqual(int(encoded[1]), 0xDF48);

	Check(u::utf16::isFirstSurrogate(encoded[0]));
	Check(u::utf16::isSecondSurrogate(encoded[1]));
}

void test_invalid_input()
{
	// a lone trail byte
	std::string const lone_trail("\x80\x41", 2);
	u::code_point cp = 0;
	std::string::const_iterator it =
		u::utf8::decode(lone_trail.begin(), lone_trail.end(), cp);
	Check(!u::isValidCodepoint(cp));
	Check(it != lone_trail.begin());

	// a truncated sequence
	std::string const truncated("\xE2\x82", 2);
	it = u::utf8::decode(truncated.begin(), truncated.end(), cp);
	Check(!u::isValidCodepoint(cp));
	Check(it == truncated.end());
}

void test_widen_narrow()
{
	char const* strings[] = {
		"",
		"ascii",
		"\xC2\xA2",                 // cent sign
		"\xE2\x82\xAC",             // euro sign
		"\xF0\x90\x8D\x88",         // gothic hwair
		"mixed \xE2\x82\xAC 42"
	};

	size_t const count = sizeof(strings) / sizeof(strings[0]);
	for (size_t i = 0; i < count; ++i) {
		std::string const source(strings[i]);
		std::wstring const wide = aw::unicode::widen(source);
		std::string const back  = aw::unicode::narrow(wide);

		CheckEqualCtx(back, source, " [\"" + source + "\"]");
	}
}
} // namespace

int main()
{
	test_widths();
	test_utf8_encoding();
	test_utf16_surrogates();
	test_roundtrip<u::utf8>("utf8");
	test_roundtrip<u::utf16>("utf16");
	test_roundtrip<u::utf32>("utf32");
	test_invalid_input();
	test_widen_narrow();

	return awstd_test::result();
}
