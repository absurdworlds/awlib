/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_hdf_value_h
#define aw_hdf_value_h
#include <cstring>
#include <string>

#include <aw/types/variant.h>
#include <aw/math/vector2d.h>
#include <aw/math/vector3d.h>
#include <aw/math/vector4d.h>
#include <aw/utility/to_string.h>
#include <aw/utility/to_string/math/vector.h>

#include <aw/fileformat/hdf/type.h>

namespace aw {
namespace hdf {
//! Class for holding any HDF Value.
struct Value {
	Value()
	{
	}

	template<typename val_type>
	Value(val_type v)
		: holder()
	{
		holder.set<val_type>(v);
	}

	/*! Assignment operator. Copies content from another
	 *  Value class, overwriting existing contents.
	 */
	Value& operator = (Value const& other)
	{
		holder = other.holder;
		return *this;
	}

	/*!
	 * Get value if types match.
	 * \param v
	 *     Reference to variable which will hold result.
	 *     Will be modified only if types match
	 * \return
	 *     true on success, false on failure.
	 */
	template<typename val_type>
	bool get(val_type& v) const
	{
		return holder.get(v);
	}

	template<typename val_type>
	val_type const* get() const
	{
		return holder.get<val_type>();
	}

	//! Returns type of currently held value
	hdf::Type getType() const
	{
		return convertType();
	}

	//! Set value if types are matching
	template<typename val_type>
	bool trySet(val_type const& v)
	{
		if(compareType(holder.type_index(), v)) {
			holder.set<val_type>(v);
			return true;
		}
		return false;
	}

	//! Set value, resetting type
	template<typename val_type>
	void set(val_type const& v)
	{
		holder.set<val_type>(v);
	}

	//! Reset value to <Unknown>
	void reset()
	{
		holder.reset();
	}

private:
	using holder_t = variant<
		bool, i64, f64,
		std::string,
		math::vector2d<f32>,
		math::vector3d<f32>,
		math::vector4d<f32>
	>;

	holder_t holder;

	hdf::Type convertType() const
	{
		switch (holder.type_index()) {
		case holder_t::index_of<bool>:
			return hdf::Type::Boolean;
		case holder_t::index_of<i64>:
			return hdf::Type::Integer;
		case holder_t::index_of<f64>:
			return hdf::Type::Float;
		case holder_t::index_of<std::string>:
			return hdf::Type::String;
		case holder_t::index_of<math::vector2d<f32>>:
			return hdf::Type::Vector2d;
		case holder_t::index_of<math::vector3d<f32>>:
			return hdf::Type::Vector3d;
		case holder_t::index_of<math::vector4d<f32>>:
			return hdf::Type::Vector4d;
		case holder_t::invalid:
			return hdf::Type::Unknown;
		};
	}
};

//! Convert Value to string
inline std::string to_string(Value const& val)
{
	using aw::to_string;
	switch (val.getType()) {
	case hdf::Type::String:
		return to_string(*val.get<std::string>());
	case hdf::Type::Float:
		return to_string(*val.get<f64>());
	case hdf::Type::Integer:
		return to_string(*val.get<i64>());
	case hdf::Type::Boolean:
		return to_string(*val.get<bool>());
	case hdf::Type::Vector2d:
		return to_string(*val.get<math::vector2d<f32>>());
	case hdf::Type::Vector3d:
		return to_string(*val.get<math::vector3d<f32>>());
	case hdf::Type::Vector4d:
		return to_string(*val.get<math::vector4d<f32>>());
	default:
		break;
	}

	return "null";
}
} // namespace hdf
} // namespace aw
#endif//aw_hdf_value_h
