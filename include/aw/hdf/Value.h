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

#include <aw/common/types.h>
#include <aw/math/Vector2d.h>
#include <aw/math/Vector3d.h>
#include <aw/math/Vector4d.h>

#include <aw/hdf/Type.h>

namespace aw {
namespace hdf {
//! Class for holding any HDF Value.
class Value {
public:
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

	//! Returns type of currently held value
	hdf::Type getType() const
	{
		return holder.type;
	}

	//! Set value if types are matching
	template<typename val_type>
	bool trySet(val_type const& v)
	{
		if(compareType(holder.type, v)) {
			holder.set<val_type>(v);
			return true;
		}
		return false;
	}

	//! Set value, resetting type
	template<typename val_type>
	void set(val_type const v)
	{
		holder.set<val_type>(v);
	}

	//! Reset value to <Unknown>
	void reset()
	{
		holder.reset();
	}

private:
	template <typename... Ts>
	struct Helper;

	template <typename T, typename... Ts>
	struct Helper<T, Ts...> {
		static void destroy(Type type, void* data)
		{
			if (checkType<T>(type))
				reinterpret_cast<T*>(data)->~T();
			else
				Helper<Ts...>::destroy(type, data);
		}
		static void copy(Type type, void const* from, void* to)
		{
			if (checkType<T>(type))
				new (to) T(*reinterpret_cast<T const*>(from));
			else
				Helper<Ts...>::copy(type, from, to);
		}
		static void move(Type type, void* from, void* to)
		{
			if (checkType<T>(type))
				new (to) T(std::move(from));
			else
				Helper<Ts...>::move(type, from, to);
		}
	};


	template <typename... Ts>
	struct Holder {
		static size_t const size = std::max({sizeof(Ts)...});
		static size_t const align = std::max({alignof(Ts)...});

		typedef typename std::aligned_storage<size, align>::type storage;
		typedef Helper<Ts...> helper;

		hdf::Type type;
		storage data;

		Holder()
			: type(Type::Unknown)
		{
		}

		template<typename T, typename... Args>
		Holder(Args&&... args)
		{
			set<T>(std::forward<Args>(args)...);
		}

		Holder(Holder<Ts...> const& other)
			: type(other.type)
		{
			helper::copy(other.type, &other.data, &data);
		}

		Holder(Holder<Ts...>&& other)
			: type(other.type)
		{
			helper::move(other.type, &other.data, &data);
		}

		Holder<Ts...>& operator=(Holder<Ts...> const& other)
		{
			helper::destroy(type, &data);
			helper::copy(other.type, &other.data, &data);
			type = other.type;
			return *this;
		}

		~Holder()
		{
			reset();
		}

		template<typename T, typename... Args>
		void set(Args&&... args)
		{
			helper::destroy(type, &data);
			new (&data) T(std::forward<Args>(args)...);
			type = typeof<T>::value;	
		}

		template<typename T>
		bool get(T& target) const
		{
			if (checkType<T>(type)) {
				target = *reinterpret_cast<T const*>(&data);
				return true;
			}
			return false;
		}

		void reset()
		{
			helper::destroy(type, &data);
		}
	};

	typedef Holder<bool, i64, f64, std::string,
	       Vector2d<f32>, Vector3d<f32>, Vector4d<f32>> holder_t;
	holder_t holder;
};

template <>
struct Value::Helper<> {
	static void destroy(Type type, void* data) { }
	static void copy(Type type, void const* from, void* to) { }
	static void move(Type type, void* from, void* to) { }
};
} // namespace hdf

//! Convert Value to string
inline std::string as_string(hdf::Value const& val)
{
// TODO: through individual as_string
	switch (val.getType()) {
	case hdf::Type::String:
		{
			std::string v;
			val.get(v);
			return v;
		}
	case hdf::Type::Float:
		{
			f64 f;
			val.get(f);
			return std::to_string(f);
		}
	case hdf::Type::Integer:
		{
			i64 i;
			val.get(i);
			return std::to_string(i);
		}
	case hdf::Type::Boolean:
		{
			bool b;
			val.get(b);
			return std::to_string(b);
		}
	case hdf::Type::Vector2d:
		{
			Vector2d<f32> v;
			val.get(v);
			return std::to_string(v[0]) + ", " +
			       std::to_string(v[1]);
		}
	case hdf::Type::Vector3d:
		{
			Vector3d<f32> v;
			val.get(v);
			return std::to_string(v[0]) + ", " +
			       std::to_string(v[1]) + ", " +
			       std::to_string(v[2]);
		}
	case hdf::Type::Vector4d:
		{
			Vector4d<f32> v;
			val.get(v);
			return std::to_string(v[0]) + ", " +
			       std::to_string(v[1]) + ", " +
			       std::to_string(v[2]) + ", " +
			       std::to_string(v[3]);
		}
	}

	return "null";
}
} // namespace aw
#endif//_aw_hdf_value_
