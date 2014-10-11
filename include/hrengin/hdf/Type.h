/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hdf_Type_
#define _hrengin_hdf_Type_

namespace hrengin {
namespace hdf {

/*! Enumeration of possible HDF value types */
enum class Type {
	Integer,
	Float,
	Boolean,
	String,
	Vector2d,
	Vector3d,
	Vector4d,
	Enum,
	Unknown
};

template<typename T>
inline bool checkType (hdf::Type type)
{
	return false;
}

template<>
inline bool checkType<i32> (hdf::Type type)
{
	return Type::Integer == type;
}

template<>
inline bool checkType<u32> (hdf::Type type)
{
	return Type::Integer == type;
}

template<>
inline bool checkType<i64> (hdf::Type type)
{
	return Type::Integer == type;
}

template<>
inline bool checkType<u64> (hdf::Type type)
{
	return Type::Integer == type;
}

template<>
inline bool checkType<f32> (hdf::Type type)
{
	return Type::Float == type;
}

template<>
inline bool checkType<f64> (hdf::Type type)
{
	return Type::Float == type;
}

template<>
inline bool checkType<bool> (hdf::Type type)
{
	return Type::Boolean == type;
}

template<>
inline bool checkType<std::string> (hdf::Type type)
{
	return Type::String == type;
}

template<>
inline bool checkType<Vector2d<f32>> (hdf::Type type)
{
	return Type::Vector2d == type;
}

template<>
inline bool checkType<Vector3d<f32>> (hdf::Type type)
{
	return Type::Vector3d == type;
}

template<typename T>
inline hdf::Type deduceType ()
{
	return Type::Unknown;
}

template<>
inline hdf::Type deduceType<i32> ()
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType<u32> ()
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType<i64> ()
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType<u64> ()
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType<f32> ()
{
	return Type::Float;
}

template<>
inline hdf::Type deduceType<f64> ()
{
	return Type::Float;
}

template<>
inline hdf::Type deduceType<bool> ()
{
	return Type::Boolean;
}

template<>
inline hdf::Type deduceType<std::string> ()
{
	return Type::String;
}

template<>
inline hdf::Type deduceType<Vector2d<f32>> ()
{
	return Type::Vector2d;
}

template<>
inline hdf::Type deduceType<Vector3d<f32>> ()
{
	return Type::Vector3d;
}


template<typename T>
inline bool checkType (hdf::Type type, T)
{
	return false;
}

template<>
inline bool checkType (hdf::Type type, i32)
{
	return Type::Integer == type;
}

template<>
inline bool checkType (hdf::Type type, u32)
{
	return Type::Integer == type;
}

template<>
inline bool checkType (hdf::Type type, i64)
{
	return Type::Integer == type;
}

template<>
inline bool checkType (hdf::Type type, u64)
{
	return Type::Integer == type;
}

template<>
inline bool checkType (hdf::Type type, f64)
{
	return Type::Float == type;
}

template<>
inline bool checkType (hdf::Type type, bool)
{
	return Type::Boolean == type;
}

template<>
inline bool checkType (hdf::Type type, std::string)
{
	return Type::String == type;
}

template<>
inline bool checkType (hdf::Type type, Vector2d<f32>)
{
	return Type::Vector2d == type;
}

template<>
inline bool checkType (hdf::Type type, Vector3d<f32>)
{
	return Type::Vector3d == type;
}

template<typename T>
inline hdf::Type deduceType (T)
{
	return Type::Unknown;
}

template<>
inline hdf::Type deduceType (i32)
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType (u32)
{
	return Type::Integer;
}


template<>
inline hdf::Type deduceType (i64)
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType (u64)
{
	return Type::Integer;
}

template<>
inline hdf::Type deduceType (f32)
{
	return Type::Float;
}

template<>
inline hdf::Type deduceType (f64)
{
	return Type::Float;
}

template<>
inline hdf::Type deduceType (bool)
{
	return Type::Boolean;
}

template<>
inline hdf::Type deduceType (std::string)
{
	return Type::String;
}

template<>
inline hdf::Type deduceType (Vector2d<f32>)
{
	return Type::Vector2d;
}

template<>
inline hdf::Type deduceType (Vector3d<f32>)
{
	return Type::Vector3d;
}

} // namespace hdf
} // namespace hrengin

#endif//_hrengin_hdf_Type_
