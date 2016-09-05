/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_hdf_value_
#define _aw_hdf_value_
#include <cstring>
#include <string>

#include <aw/types/variant.h>
#include <aw/types/optional.h>
#include <aw/math/Vector2d.h>
#include <aw/math/Vector3d.h>
#include <aw/math/Vector4d.h>
#include <aw/utility/string/as_string.h>
#include <aw/math/utils/as_string.h>

#include <aw/hdf/Type.h>

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
	optional<val_type> get() const
	{
		val_type tmp;

		if (holder.get(tmp))
			return tmp;

		return nullopt;
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
	using holder_t = variant<bool, i64, f64, std::string,
	       Vector2d<f32>, Vector3d<f32>, Vector4d<f32>>;

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
		case holder_t::index_of<Vector2d<f32>>:
			return hdf::Type::Vector2d;
		case holder_t::index_of<Vector3d<f32>>:
			return hdf::Type::Vector3d;
		case holder_t::index_of<Vector4d<f32>>:
			return hdf::Type::Vector4d;
		case holder_t::invalid:
			return hdf::Type::Unknown;
		};
	}
};
} // namespace hdf

//! Convert Value to string
inline std::string as_string(hdf::Value const& val)
{
	switch (val.getType()) {
	case hdf::Type::String:
		return as_string(val.get<std::string>());
	case hdf::Type::Float:
		return as_string(val.get<f64>());
	case hdf::Type::Integer:
		return as_string(val.get<i64>());
	case hdf::Type::Boolean:
		return as_string(val.get<bool>());
	case hdf::Type::Vector2d:
		return as_string(val.get<Vector2d<f32>>());
	case hdf::Type::Vector3d:
		return as_string(val.get<Vector3d<f32>>());
	case hdf::Type::Vector4d:
		return as_string(val.get<Vector4d<f32>>());
	default:
		break;
	}

	return "null";
}
} // namespace aw
#endif//_aw_hdf_value_
