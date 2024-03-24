/*
 * Copyright (C) 2014-2020 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_hudf_type_h
#define aw_hudf_type_h
#include <string>
#include <vector>
#include <aw/meta/conditional.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/types.h>

namespace aw {
template<typename>
struct is_vector_t : std::false_type{ };
template<class T, class Alloc>
struct is_vector_t<std::vector<T, Alloc>> : std::true_type{ };

template<typename, template <typename> typename>
struct is_vector_of_t : std::false_type{ };
template<class T, class Alloc, template <typename> typename Pred>
struct is_vector_of_t<std::vector<T, Alloc>, Pred> : Pred<T> { };

template<typename T>
constexpr bool is_vector = is_vector_t<T>::value;

template<typename T, template <typename> typename Pred>
constexpr bool is_vector_of = is_vector_of_t<T, Pred>::value;

namespace hudf {
/*!
 * Enumeration of possible value types
 */
enum class type {
	unknown,
	boolean,
	integer,
	floating_point,
	string,
	boolean_vector,
	integer_vector,
	float_vector,
	string_vector
};

namespace _impl {
template<typename T>
constexpr auto type_of() -> enable_if<is_int<T>, type>   { return type::integer; }
template<typename T>
constexpr auto type_of() -> enable_if<is_vector_of<T, is_int_t>, type>
{
	return type::integer_vector;
}

template<typename T>
constexpr auto type_of() -> enable_if<is_float<T>, type> { return type::floating_point; }
template<typename T>
constexpr auto type_of() -> enable_if<is_vector_of<T, is_float_t>, type>
{
	return type::float_vector;
}

template<typename T>
constexpr type type_of()
{
	return type::unknown;
}

template<>
constexpr type type_of<std::string>()              { return type::string; }
template<>
constexpr type type_of<std::vector<std::string>>() { return type::string; }

template<>
constexpr type type_of<bool>()              { return type::boolean; }
template<>
constexpr type type_of<std::vector<bool>>() { return type::boolean; }
} // namespace _impl

/*!
 * Value corresponding to type T
 */
template<typename T>
constexpr type type_of = _impl::type_of<T>();

/*!
 * Compare type of a value \a val to the type \a type.
 */
template<typename T>
inline bool operator==(hudf::type type, T const& val)
{
	return type == type_of<T>;
}
} // namespace hudf
} // namespace aw
#endif//aw_hudf_type_h
