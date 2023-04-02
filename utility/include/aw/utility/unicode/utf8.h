/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_utf8_h
#define aw_utility_utf8_h
#include <aw/utility/unicode/unicode.h>
namespace aw::unicode::utf8 {
using char_type   = char8_t;
using string      = std::string;

enum head_char : char_type {
	begin            = 0xC0,
	valid_begin      = 0xC2,
	three_byte_begin = 0xE0,
	four_byte_begin  = 0xF0,
	valid_end        = 0xF5,
};

enum marker : char_type {
	tail_mask       = 0xC0,
	tail            = 0x80,
	start_2byte_seq = 0xC0,
	start_3byte_seq = 0xE0,
	start_4byte_seq = 0xF0,
};

/*!
 * Returns width of UTF-8 encoding of specific code point
 */
inline size_t width(code_point cp)
{
	enum code_point {
		single_byte_cp_end = 0x80,
		two_byte_cp_end    = 0x800,
		three_byte_cp_end  = 0x10000,
		four_byte_cp_end   = 0x110000,
	};

	if (cp < single_byte_cp_end)
		return 1;
	if (cp < two_byte_cp_end)
		return 2;
	if (cp < three_byte_cp_end)
		return 3;
	if (cp < four_byte_cp_end)
		return 4;

	return 0;
}

/*!
 * \return true if \a ch is a single-byte ASCII character
 */
inline bool is_ascii(char_type ch)
{
	constexpr char_type ascii_end = 0x80;
	return ch < ascii_end;
}

/*!
 * \return true if character is a valid continuation byte
 */
inline bool is_tail(char_type ch)
{
	return (ch & marker::tail_mask) == marker::tail;
}

/*!
 * \return Is the \a lead a valid start of multi-byte encoding.
 * \note Character that technically can start multi-byte encoding,
 *       but is not valid under the UTF-8 spec is not considered valid.
 */
inline bool is_head(char_type ch)
{
	return (head_char::valid_begin <= ch) && (ch < head_char::valid_end);
}

/*!
 * \return How many characters follow the head, or -1 if the
 *         \a lead is not a valid start of multi-byte encoding.
 */
inline size_t tail_length(char_type lead)
{
	if (!is_head(lead))
		return -1;
	if (lead < head_char::three_byte_begin)
		return 1;
	if (lead < head_char::four_byte_begin)
		return 2;
	return 3;
}

inline bool is_valid_code_unit(char_type unit)
{
	// equivalent to
	// is_ascii(unit) || is_tail(unit) || is_head(unit);
	return unit < head_char::begin || is_head(unit);
}

using sextet = bitword<6, char_type>;


struct codec {
	using char_type   = utf8::char_type;
	using string      = utf8::string;

	/*!
	 * Encode code point in UTF-8 and append it to a string
	 * Does not check if the code point is valid
	 */
	template<typename Iterator>
	static Iterator encode(code_point cp, Iterator output)
	{
		switch (width(cp)) {
		case 1:
			*(output++) = char_type(cp);
			break;
		case 2:
			*(output++) = sextet::get(cp, 1) | marker::start_2byte_seq;
			*(output++) = sextet::get(cp, 0) | marker::tail;
			break;
		case 3:
			*(output++) = sextet::get(cp, 2) | marker::start_3byte_seq;
			*(output++) = sextet::get(cp, 1) | marker::tail;
			*(output++) = sextet::get(cp, 0) | marker::tail;
			break;
		case 4:
			*(output++) = sextet::get(cp, 3) | marker::start_4byte_seq;
			*(output++) = sextet::get(cp, 2) | marker::tail;
			*(output++) = sextet::get(cp, 1) | marker::tail;
			*(output++) = sextet::get(cp, 0) | marker::tail;
		}

		// invalid, skip
		return output;
	}

	/*!
	 * Advance to the next sequence of code units
	 */
	template<typename Iterator>
	static Iterator next(Iterator input, Iterator end)
	{
		while ((input < end) && !is_head(*input) && !is_ascii(*input))
			++input;

		return input;
	}

	/*!
	 * Decode UTF-8 sequence, if valid
	 */
	template<typename Iterator>
	static Iterator decode(Iterator input, Iterator end, code_point& cp)
	{
		// bail out with an error
		auto error = [&cp] (Iterator ret) {
			cp = -1;
			return ret;
		};

		if (input == end)
			return error(input);

		constexpr size_t byte_mask = 0xFF;
		cp = *(input++) & byte_mask;
		if (is_ascii(cp))
			return input;

		size_t length = tail_length(cp);
		if (length == -1)
			return error(input);

		const size_t data_mask = sextet::mask >> length;

		cp = cp & data_mask;

		// clang can't properly unroll the loop,
		// and all compilers leave in checks for (i<length)
		switch (length) {
		default:
			return error(input);

		case 3: // NOLINT(bugprone-branch-clone): manually unrolled loop
			if (input == end || !is_tail(*input))
				return error(input);

			cp = sextet::add(cp, *input++);

		case 2:
			if (input == end || !is_tail(*input))
				return error(input);

			cp = sextet::add(cp, *input++);

		case 1:
			if (input == end || !is_tail(*input))
				return error(input);

			cp = sextet::add(cp, *input++);
		}

		return input;
	}
};
} // namespace aw::unicode::utf8
#endif//aw_utility_utf8_h
