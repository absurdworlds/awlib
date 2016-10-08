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
#include <aw/types/types.h>
#include <aw/types/string_view.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/is_iterable.h>
#include <aw/meta/conditional.h>

namespace aw {
namespace format {
struct pretty_print;
}

template<typename Formatter = format::pretty_print>
std::string to_string(string_view str, Formatter&& fmt = Formatter{})
{
	return fmt.value(str);
}

template<typename Formatter = format::pretty_print>
std::string to_string(std::string const& str, Formatter&& fmt = Formatter{})
{
	return fmt.value(str);
}

template<typename Formatter = format::pretty_print>
std::string to_string(char const* str, Formatter&& fmt = Formatter{})
{
	return fmt.value(str);
}

template<typename Formatter = format::pretty_print>
std::string to_string(char ch, Formatter&& fmt = Formatter{})
{
	return fmt.value(ch);
}

template<typename T, typename Formatter = format::pretty_print>
auto to_string(T value, Formatter&& fmt = Formatter{}) ->
	enable_if<is_int<T>, std::string>
{
	return fmt.value(value);
}

template<typename T, typename Formatter = format::pretty_print>
auto to_string(T value, Formatter&& fmt = Formatter{}) ->
	enable_if<is_float<T>, std::string>
{
	return fmt.value(value);
}

template<typename Formatter = format::pretty_print>
std::string to_string(bool value, Formatter&& fmt = Formatter{})
{
	using namespace sv_literals;
	return fmt.literal(value ? "true"_s : "false"_s);
}

template<typename Formatter = format::pretty_print>
std::string to_string(nullptr_t, Formatter&& fmt = Formatter{})
{
	using namespace sv_literals;
	return fmt.literal("nullptr"_s);
}

template<typename T, typename Formatter = format::pretty_print>
std::string to_string(T const* ptr, Formatter&& fmt = Formatter{})
{
	return fmt.value(reinterpret_cast<void const*>(ptr));
}


template<typename T>
struct string_converter;

template <typename T, typename Formatter = format::pretty_print>
auto to_string(T const& value, Formatter&& fmt = Formatter{}) ->
	decltype( declval<string_converter<T>>()(fmt) )
{
	return string_converter<T>{value}(fmt);
}

template<typename T, typename Formatter = format::pretty_print>
auto to_string(T const& range, Formatter&& fmt = Formatter{}) ->
	enable_if<is_const_iterable<T>, std::string>
{
	fmt.list_start();
	for (auto const& value : range)
		fmt.value(value);
	fmt.list_end();
	return fmt;
}

template<typename InputIt, typename Formatter = format::pretty_print>
std::string to_string(InputIt begin, InputIt end, Formatter&& fmt = Formatter{})
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
