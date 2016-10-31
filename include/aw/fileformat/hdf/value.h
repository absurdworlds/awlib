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
#include <aw/utility/to_string.h>
#include <aw/utility/to_string/variant.h>

#include <aw/fileformat/hdf/type.h>

namespace aw {
namespace hdf {
inline namespace v1 {
//! Class for holding any HDF value.
struct value {
	value() = default;
	value(value const&) = default;
	value(value&&) = default;

	explicit value(bool v)
		: holder{ v }
	{ }

	template<typename T, bool_if<is_int<T>> = true>
	explicit value(T v)
		: holder{ intmax_t{v} }
	{ }

	template<typename T, bool_if<is_float<T>> = true>
	explicit value(T v)
		: holder{ double{v} }
	{ }

	template<typename T, bool_if<is_constructible<std::string,T>> = true>
	explicit value(T&& v)
		: holder()
	{
		holder.emplace<std::string>(std::forward<T>(v));
	}

	template<typename T, bool_if<is_vector<T>> = true>
	explicit value(T&& v)
		: holder(v)
	{
	}

	value& operator=(value const& other)
	{
		holder = other.holder;
		return *this;
	}

	value& operator=(value&& other)
	{
		holder = std::move(other.holder);
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
	template<typename T>
	bool get(T& v) const
	{
		return holder.get(v);
	}

	template<typename T>
	T const* get() const
	{
		return holder.get<T>();
	}

	template<typename T>
	T try_get(T const& _default)
	{
		T tmp;
		return get(tmp) ? tmp : _default;
	}

	//! Returns type of currently held value
	hdf::Type get_type() const
	{
		return convert_type();
	}

	//! Set value, resetting type
	template<typename val_type>
	void set(val_type const& v)
	{
		holder.set<val_type>(v);
	}

	//! Set value if types are matching
	template<typename val_type>
	bool try_set(val_type const& v)
	{
		if(compareType(holder.type_index(), v)) {
			holder.set<val_type>(v);
			return true;
		}
		return false;
	}

	bool empty() const
	{
		return holder.empty();
	}

	//! Reset value to <Unknown>
	void reset()
	{
		holder.reset();
	}

	operator bool() const
	{
		return !empty();
	}

	friend std::string to_string(value const& val)
	{
		using aw::to_string;
		return to_string(val.holder);
	}

private:
	using holder_t = variant<
		bool, intmax_t, double,
		std::string,
		std::vector<bool>,
		std::vector<intmax_t>,
		std::vector<double>,
		std::vector<std::string>
	>;

	holder_t holder;

	hdf::Type convert_type() const
	{
		switch (holder.type_index()) {
		case holder_t::index_of<bool>:
			return hdf::Type::Boolean;
		case holder_t::index_of<intmax_t>:
			return hdf::Type::Integer;
		case holder_t::index_of<double>:
			return hdf::Type::Float;
		case holder_t::index_of<std::string>:
			return hdf::Type::String;
		case holder_t::index_of<std::vector<bool>>:
			return hdf::Type::BooleanVector;
		case holder_t::index_of<std::vector<intmax_t>>:
			return hdf::Type::IntegerVector;
		case holder_t::index_of<std::vector<double>>:
			return hdf::Type::FloatVector;
		case holder_t::index_of<std::vector<std::string>>:
			return hdf::Type::StringVector;
		case holder_t::invalid:
			return hdf::Type::Unknown;
		};
	}
};
} // inline namespace v1
} // namespace hdf
} // namespace aw
#endif//aw_hdf_value_h
