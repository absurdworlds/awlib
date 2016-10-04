/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_hdf_Type_h
#define aw_hdf_Type_h
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

namespace hdf {
/*!
 * Enumeration of possible HDF value types
 */
enum class Type {
	Unknown,
	Boolean,
	Integer,
	Float,
	String,
	BooleanVector,
	IntegerVector,
	FloatVector,
	StringVector
};

namespace _impl {
template<typename T>
constexpr auto typeof() -> enable_if<is_int<T>, Type>   { return Type::Integer; }
template<typename T>
constexpr auto typeof() -> enable_if<is_vector_of<T, is_int_t>, Type>
{
	return Type::IntegerVector;
}

template<typename T>
constexpr auto typeof() -> enable_if<is_float<T>, Type> { return Type::Float; }
template<typename T>
constexpr auto typeof() -> enable_if<is_vector_of<T, is_float_t>, Type>
{
	return Type::FloatVector;
}

template<typename T>
constexpr Type typeof()
{
	return Type::Unknown;
}

template<>
constexpr Type typeof<std::string>()              { return Type::String; }
template<>
constexpr Type typeof<std::vector<std::string>>() { return Type::String; }

template<>
constexpr Type typeof<bool>()              { return Type::Boolean; }
template<>
constexpr Type typeof<std::vector<bool>>() { return Type::Boolean; }
} // namespace _impl

/*!
 * HDF type corresponding to type T
 */
template<typename T>
constexpr Type typeof = _impl::typeof<T>();

/*!
 * Compare type of a value \a val to the type \a type.
 */
template<typename T>
inline bool operator==(hdf::Type type, T const& val)
{
	return type == typeof<T>;
}
} // namespace hdf
} // namespace aw
#endif//aw_hdf_Type_h
