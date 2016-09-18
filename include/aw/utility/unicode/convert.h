/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_utf_convert_
#define _aw_utf_convert_
#include <aw/utility/string/string.h>
#include <aw/utility/unicode/utf8.h>
#include <aw/utility/unicode/utf16.h>
#include <aw/utility/unicode/utf32.h>

#include <aw/meta/conditional.h>
#include <aw/types/traits/basic_traits.h>
namespace aw {
namespace unicode {
namespace _impl {
template<typename String>
struct encoding_of;
template<> struct encoding_of<utf8::string>  { using type = utf8; };
template<> struct encoding_of<utf16::string> { using type = utf16; };
template<> struct encoding_of<utf32::string> { using type = utf32; };
template<> struct encoding_of<std::wstring>  {
private:
	static constexpr size_t _wsize = sizeof(std::wstring::value_type);
public:
	using type = conditional<_wsize == sizeof(char32_t), utf32,
	             conditional<_wsize == sizeof(char16_t), utf16,
	             conditional<_wsize == sizeof(char),     utf8, void>>>;
};
} // namespace _impl;
template<typename String>
using encoding_of = typename _impl::encoding_of<String>::type;

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

//! Convert string between different Unicode encodings
template<typename In, typename Out>
auto convert(typename In::string const& str) -> typename Out::string
{
	return convert<typename Out::string>(str, In{}, Out{});
}

template<typename Out, typename In>
auto convert(In const& str) ->
	enable_if<is_string<Out> && is_string<In>, Out>
{
	return convert<Out>(str, encoding_of<In>{}, encoding_of<Out>{});
}

namespace {
constexpr utf8::string(&narrow)(utf16::string const&) = convert<utf16, utf8>;
constexpr utf16::string(&widen)(utf8::string const&)  = convert<utf8, utf16>;
}
} // namespace unicode
} // namespace aw
#endif//_aw_utf_convert_
