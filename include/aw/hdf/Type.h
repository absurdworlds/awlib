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
#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/conditional.h>
#include <aw/types/types.h>

namespace aw {
template <typename T, size_t N>
class Vector;

namespace hdf {
/*!
 * Enumeration of possible HDF value types
 */
enum class Type {
	Unknown,
	Integer,
	Float,
	Boolean,
	String,
	Vector2d,
	Vector3d,
	Vector4d,
	Enum,
};

template<typename T>
struct typeof {
	static constexpr Type value =
	is_int<T>   ? Type::Integer :
	is_float<T> ? Type::Float   : Type::Unknown;
};


template<>
struct typeof<bool> {
	static constexpr Type value = Type::Boolean;
};

template<>
struct typeof<std::string> {
	static constexpr Type value = Type::String;
};

template<>
struct typeof<Vector<f32,2>> {
	static constexpr Type value = Type::Vector2d;
};

template<>
struct typeof<Vector<f32,3>> {
	static constexpr Type value = Type::Vector3d;
};

template<>
struct typeof<Vector<f32,4>> {
	static constexpr Type value = Type::Vector4d;
};

/*!
 * Template function used to deduce HDF type from C++ type
 */
template<typename T>
inline hdf::Type deduceType(T)
{
	return typeof<T>::value;
}

/*!
 * Template function used to check if C++ type corresponds to HDF type \a type
 */
template<typename T>
inline bool checkType(hdf::Type type)
{
	return typeof<T>::value == type;
}

/*!
 * Compare type of a value \a val to the type \a type.
 */
template<typename T>
inline bool compareType(hdf::Type type, T val)
{
	return type == deduceType(val);
}

/*!
 * Compare type of a value \a val to the type \a type.
 */
template<typename T>
inline bool operator==(hdf::Type type, T val)
{
	return compareType(type, val);
}
} // namespace hdf
} // namespace aw
#endif//aw_hdf_Type_h
