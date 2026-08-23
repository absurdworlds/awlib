/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_to_string_h
#define aw_to_string_h
#include <string>
#include <initializer_list>
#include <aw/types/types.h>
#include <aw/types/string_view.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/is_iterable.h>
#include <aw/meta/conditional.h>

namespace aw {
namespace formatter {
struct pretty_print;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(string_view str, Formatter&& fmt = Formatter{})
{
	fmt.convert(str);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(std::string const& str, Formatter&& fmt = Formatter{})
{
	fmt.convert(str);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(char const* str, Formatter&& fmt = Formatter{})
{
	fmt.convert(str);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(char ch, Formatter&& fmt = Formatter{})
{
	fmt.convert(ch);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(char16_t ch, Formatter&& fmt = Formatter{})
{
	fmt.convert(ch);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(char32_t ch, Formatter&& fmt = Formatter{})
{
	fmt.convert(ch);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(wchar_t ch, Formatter&& fmt = Formatter{})
{
	fmt.convert(ch);
	return fmt;
}

template<typename T, typename Formatter = formatter::pretty_print>
auto to_string(T value, Formatter&& fmt = Formatter{}) ->
	enable_if<is_int<T>, std::string>
{
	fmt.convert(value);
	return fmt;
}

template<typename T, typename Formatter = formatter::pretty_print>
auto to_string(T value, Formatter&& fmt = Formatter{}) ->
	enable_if<is_float<T>, std::string>
{
	fmt.convert(value);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(bool value, Formatter&& fmt = Formatter{})
{
	fmt.convert(value);
	return fmt;
}

template<typename Formatter = formatter::pretty_print>
std::string to_string(nullptr_t value, Formatter&& fmt = Formatter{})
{
	fmt.convert(value);
	return fmt;
}

template<typename T, typename Formatter = formatter::pretty_print>
std::string to_string(T const* ptr, Formatter&& fmt = Formatter{})
{
	fmt.convert(reinterpret_cast<void const*>(ptr));
	return fmt;
}

template<typename T>
struct string_converter;

template <typename T, typename Formatter = formatter::pretty_print>
auto to_string(T const& value, Formatter&& fmt = Formatter{}) ->
	decltype( declval<string_converter<T>>()(fmt) )
{
	return string_converter<T>{value}(fmt);
}


template<typename T, typename Formatter = formatter::pretty_print>
auto to_string(T const& range, Formatter&& fmt = Formatter{}) ->
	enable_if<is_const_iterable<T>, std::string>;

template<typename InputIt, typename Formatter = formatter::pretty_print>
std::string to_string(InputIt begin, InputIt end, Formatter&& fmt);


template<typename T, typename Formatter = formatter::pretty_print>
std::string to_string(std::initializer_list<T> ilist, Formatter&& fmt = Formatter{})
{
	return to_string(begin(ilist), end(ilist), fmt);
}

template<typename T, typename Formatter>
auto to_string(T const& range, Formatter&& fmt) ->
	enable_if<is_const_iterable<T>, std::string>
{
	fmt.list_start();
	for (auto const& value : range)
		fmt.value(value);
	fmt.list_end();
	return fmt;
}

template<typename InputIt, typename Formatter>
std::string to_string(InputIt begin, InputIt end, Formatter&& fmt)
{
	fmt.list_start();
	while (begin != end)
		fmt.value(*begin++);
	fmt.list_end();
	return fmt;
}
} // namespace aw

#include <aw/utility/to_string/formatters/pretty-print.h>
#endif//aw_string_to_string_h
