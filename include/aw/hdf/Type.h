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
	static Type const value = Type::Unknown;
};

template<typename T>
struct typeof<enable_if<is_int<T>, T>> {
	static Type const value = Type::Integer;
};

template<typename T>
struct typeof<enable_if<is_float<T>, T>> {
	static Type const value = Type::Float;
};

template<typename T>
struct typeof<enable_if<is_bool<T>, T>> {
	static Type const value = Type::Boolean;
};

template<>
struct typeof<std::string> {
	static Type const value = Type::String;
};

template<>
struct typeof<Vector<f32,2>> {
	static Type const value = Type::Vector2d;
};

template<>
struct typeof<Vector<f32,3>> {
	static Type const value = Type::Vector3d;
};

template<>
struct typeof<Vector<f32,4>> {
	static Type const value = Type::Vector4d;
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
inline bool operator == (hdf::Type type, T val)
{
	return compareType(type, val) ;
}
} // namespace hdf
} // namespace aw
#endif//aw_hdf_Type_h
