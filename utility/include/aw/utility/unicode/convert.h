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
#include <iterator>

namespace aw {
namespace encoding { struct unknown {}; }
namespace unicode {
template <typename CharT>
constexpr encoding::unknown char_encoding;

template<> inline constexpr utf8::codec  char_encoding<char>;
template<> inline constexpr utf8::codec  char_encoding<char8_t>;
template<> inline constexpr utf16::codec char_encoding<char16_t>;
template<> inline constexpr utf32::codec char_encoding<char32_t>;

namespace _impl {
struct wchar_enc {
private:
	static constexpr size_t size = sizeof(std::wstring::value_type);
public:
	using type = conditional<size <= sizeof(char),     utf8::codec,
	             conditional<size <= sizeof(char16_t), utf16::codec,
	             conditional<size <= sizeof(char32_t), utf32::codec,
	                                                   encoding::unknown>>>;
};
} // namespace _impl

template<> inline constexpr _impl::wchar_enc::type char_encoding<wchar_t>;


template<typename String>
constexpr decltype( char_encoding<typename String::value_type> ) encoding_of;

struct parser_parameters {
	bool* error = nullptr;
	bool stop_on_error = false;
};

//! Convert string between different Unicode encodings
template<typename Output, typename Input, typename In_enc, typename Out_enc>
auto convert(Input const& str, In_enc input_codec, Out_enc output_codec, parser_parameters params = {})
	-> Output
{
	auto begin = std::begin(str);
	auto end   = std::end(str);

	Output result;
	auto out = std::back_inserter(result);

	while (begin != end) {
		code_point cp = invalid;

		begin = input_codec.template decode(begin, end, cp);
		if ( !is_valid_code_point(cp) ) {
			if (params.error)
				*params.error = true;
			if (params.stop_on_error)
				return result;
			continue;
		}
		out   = output_codec.template encode(cp, out);
	}

	return result;
}

template<typename Out, typename In>
auto convert(In const& str) -> Out
{
	return convert<Out>(str, encoding_of<In>, encoding_of<Out>);
}

template<typename Out, typename In>
auto convert(In const& str, bool& has_error) -> Out
{
	return convert<Out>(str, encoding_of<In>, encoding_of<Out>, { &has_error, true });
}

inline std::string narrow(wstring_view in)
{
	return convert<std::string>(in);
}
inline std::wstring widen(u8string_view in)
{
	return convert<std::wstring>(in);
}
inline std::wstring widen(string_view in)
{
	return convert<std::wstring>(in);
}
} // namespace unicode
} // namespace aw
#endif//aw_utf_convert_h
