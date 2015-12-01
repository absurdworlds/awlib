/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_hdf_Type_
#define _awrts_hdf_Type_
#include <string>
#include <awengine/common/types.h>

namespace awrts {
template <typename T>
class Vector2d;
template <typename T>
class Vector3d;
template <typename T>
class Vector4d;

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

template<>
struct typeof<i32> {
	static Type const value = Type::Integer;
};

template<>
struct typeof<u32> {
	static Type const value = Type::Integer;
};

template<>
struct typeof<i64> {
	static Type const value = Type::Integer;
};

template<>
struct typeof<u64> {
	static Type const value = Type::Integer;
};

template<>
struct typeof<f32> {
	static Type const value = Type::Float;
};

template<>
struct typeof<f64> {
	static Type const value = Type::Float;
};

template<>
struct typeof<bool> {
	static Type const value = Type::Boolean;
};

template<>
struct typeof<std::string> {
	static Type const value = Type::String;
};

template<>
struct typeof<Vector2d<f32>> {
	static Type const value = Type::Vector2d;
};

template<>
struct typeof<Vector3d<f32>> {
	static Type const value = Type::Vector3d;
};

template<>
struct typeof<Vector4d<f32>> {
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
} // namespace awrts
#endif//_awrts_hdf_Type_
