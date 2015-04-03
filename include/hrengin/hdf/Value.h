/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hdf_value_
#define _hrengin_hdf_value_

#include <cstring>

#include <string>

#include <hrengin/common/types.h>
#include <hrengin/math/Vector2d.h>
#include <hrengin/math/Vector3d.h>
#include <hrengin/math/Vector4d.h>

#include <hrengin/hdf/Type.h>

namespace hrengin {
namespace hdf {
//! Class for holding any HDF Value.
class Value {
public:
	~Value()
	{
		resetString();
	}

	Value()
		: val_(0), type_(Type::Unknown)
	{
	}

	template<typename val_type>
	Value(val_type v)
		: val_(v), type_(deduceType<val_type>())
	{
	}

	//! Assignment operator
	Value& operator = (const Value& other)
	{
		// reset to not pollute memory with loose strings
		resetString();
		type_ = other.type_;
		val_ = other.val_;
		return *this;
	}

	//! Get value if types match
	template<typename val_type>
	bool get(val_type& v) const
	{
		if(checkType(type_, v)) {
			val_.get(v);
			return true;
		}
		return false;
	}

	//! Get current type
	hdf::Type getType() const
	{
		return type_;
	}

	//! Set value if types are matching
	template<typename val_type>
	bool trySet(val_type const& v)
	{
		if(checkType(type_, v)) {
			val_.set(v);

			return true;
		}
		return false;
	}

	//! Set value with overriding type
	template<typename val_type>
	void set(bool const v)
	{
		resetString();
		val_.set(v);
		type_ = deduceType(v);
	}

	//! Reset value to <Unknown>
	void reset()
	{
		resetString ();
		resetType ();
	}

private:
	void resetString()
	{
		if(type_ == Type::String) {
			delete[] val_.str.data;
			val_.str.length = 0;
		}
	}

	void resetType()
	{
		type_ = Type::Unknown;
	}

	hdf::Type type_;
	union Value_ {
		~Value_()
		{
		}

		Value_(bool b)
			: boolean(b)
		{
		}

		Value_(i32 i)
			: integer(i)
		{
		}

		Value_(f64 f)
			: real(f)
		{
		}

		Value_(std::string const& s)
		{
			set(s);
		}

		Value_(Vector2d<f32> const& v)
		{
			set(v);
		}

		Value_(Vector3d<f32> const& v)
		{
			set(v);
		}

		Value_(Vector4d<f32> const& v)
		{
			set(v);
		}

		void set(bool b)
		{
			boolean = b;
		}

		void set(i32 i)
		{
			integer = i;
		}

		void set(f64 f)
		{
			real = f;
		}

		void set(std::string const& s)
		{
			str.length = s.size();
			str.data = new char[str.length];

			memcpy((void*)(str.data), s.data(), str.length);
		}

		void set(Vector2d<f32> const& v)
		{
			v.toArrayOf2(vector);
		}

		void set(Vector3d<f32> const& v)
		{
			v.toArrayOf4(vector);
		}

		void set(Vector4d<f32> const& v)
		{
			v.toArrayOf4(vector);
		}

		void get(bool& v) const
		{
			v = boolean;
		}

		void get(i32& v) const
		{
			v = integer;
		}

		void get(f64& v) const
		{
			v = real;
		}

		void get(std::string& v) const
		{
			v.assign(str.data, str.length);
		}

		void get(Vector3d<f32>& v) const
		{
			v[0] = vector[0];
			v[1] = vector[1];
			v[2] = vector[2];
		}

		bool boolean;
		i32 integer;
		f64 real;
		f32 vector[4];
		struct string {
			char const* data;
			size_t length;
		} str;
	} val_;
};

//! Specialization of trySet for string type
template<>
inline bool Value::trySet(std::string const& v)
{
	if(checkType(type_, v)) {
		resetString();
		val_.set(v);

		return true;
	}
	return false;
}

} // namespace hdf
} // namespace hrengin
#endif//_hrengin_hdf_value_
