/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utf_convert_h
#define aw_utf_convert_h
#include <aw/utility/string/string.h>
#include <aw/utility/unicode/utf8.h>
#include <aw/utility/unicode/utf16.h>
#include <aw/utility/unicode/utf32.h>

#include <aw/meta/conditional.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/string_view.h>
namespace aw {
namespace encoding { struct unknown {}; }
namespace unicode {
template<typename CharT>
constexpr encoding::unknown char_encoding;

template<> constexpr utf8  char_encoding<char>;
template<> constexpr utf16 char_encoding<char16_t>;
template<> constexpr utf32 char_encoding<char32_t>;

namespace _impl {
#if 0
constexpr auto wchar_encoding()
{
	constexpr max = std::numeric_limits<wchar_t>::max();
	if constexpr ( max >= utf32::max )
		return utf32{};
	else if constexpr ( max >= utf16::max )
		return utf16{};
	else if constexpr ( max >= utf8::max )
		return utf8{};
	return encoding::unknown;
}
#endif
struct wchar_enc {
private:
	static constexpr size_t _wsize = sizeof(std::wstring::value_type);
public:
	using type = conditional<_wsize >= sizeof(char32_t), utf32,
	             conditional<_wsize >= sizeof(char16_t), utf16,
	             conditional<_wsize >= sizeof(char),     utf8, void>>>;
};
} // namespace _impl

template<> constexpr _impl::wchar_enc::type char_encoding<wchar_t>;


template<typename String>
constexpr decltype( char_encoding<typename String::value_type> ) encoding_of;

//! Convert string between different Unicode encodings
template<typename Output, typename Input, typename InEnc, typename OutEnc>
auto convert(Input const& str, InEnc, OutEnc) -> Output
{
	auto begin = std::begin(str);
	auto end   = std::end(str);

	Output result;
	auto out = std::back_inserter(result);

	while (begin != end) {
		code_point cp;

		begin = InEnc::template decode(begin, end, cp);
		if ( !isValidCodepoint(cp) )
			continue;
		out   = OutEnc::template encode(cp, out);
	}

	return result;
}

template<typename Out, typename In>
auto convert(In const& str) -> Out
{
	return convert<Out>(str, encoding_of<In>, encoding_of<Out>);
}

inline std::string narrow(wstring_view in)
{
	return convert<std::string>(in);
}
inline std::wstring widen(string_view in)
{
	return convert<std::wstring>(in);
}
} // namespace unicode
} // namespace aw
#endif//aw_utf_convert_h
