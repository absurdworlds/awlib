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
#include <aw/types/traits/basic_traits.h>
#include <aw/meta/conditional.h>
#include <aw/meta/detect.h>
namespace aw {
inline std::string to_string(bool value)
{
	using namespace std::string_literals;
	return value ? "true"s : "false"s;
}

inline std::string to_string(int value)
{
	return std::to_string(value);
}

inline std::string to_string(long value)
{
	return std::to_string(value);
}

inline std::string to_string(long long value)
{
	return std::to_string(value);
}

inline std::string to_string(unsigned value)
{
	return std::to_string(value);
}

inline std::string to_string(unsigned long value)
{
	return std::to_string(value);
}

inline std::string to_string(unsigned long long value)
{
	return std::to_string(value);
}

inline std::string to_string(float value)
{
 	return std::to_string(value);
}

inline std::string to_string(double value)
{
	return std::to_string(value);
}

inline std::string to_string(long double value)
{
	return std::to_string(value);
}

inline std::string to_string(char* value)
{
	return {value};
}

inline std::string to_string(char const* value)
{
	return {value};
}

inline std::string to_string(std::string const& value)
{
	return value;
}

inline std::string to_string(nullptr_t)
{
	return "nullptr";
}

template<typename T>
std::string to_string(T* ptr)
{
	return to_string(uintptr_t(ptr));
}


using std::declval;
template<typename T>
struct string_converter;
template <typename T>
auto to_string(T const& value) ->
	decltype( declval<string_converter<T>>()(value) )
{
	return string_converter<T>{ }(value);
}


template<typename InputIterator>
std::string to_string(InputIterator begin, InputIterator end);

namespace _impl {
template<class T> using op_std_begin = decltype(std::begin(declval<T>()));
template<class T> using op_std_end   = decltype(std::end(declval<T>()));
template<class T> using op_begin     = decltype(begin(declval<T>()));
template<class T> using op_end       = decltype(end(declval<T>()));
template<class T> using op_m_begin   = decltype(declval<T>().begin());
template<class T> using op_m_end     = decltype(declval<T>().end());
} // namespace _impl
template<class T> constexpr auto has_begin = is_detected<_impl::op_std_begin, T>;
template<class T> constexpr auto has_end   = is_detected<_impl::op_std_end, T>;

template<typename T>
auto to_string(T const& value) -> enable_if<has_begin<T> && has_end<T>, std::string>
{
	return to_string(std::begin(value), std::end(value));
}

template<typename InputIterator>
std::string to_string(InputIterator begin, InputIterator end)
{
	std::string out;
	out.append(1,'{');
	if (begin != end) {
		out.append(to_string(*begin++));
		while (begin != end) {
			out.append(", ");
			out.append(to_string(*begin++));
		}
	}

	out.append(1,'}');
	return out;
}
} // namespace aw
#endif//aw_string_to_string_h
