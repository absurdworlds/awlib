/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hdf_value_
#define _hrengin_hdf_value_

#include <string>

#include <hrengin/common/PodString.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/types.h>

#include <hrengin/core/hdf_shared.h>

namespace hrengin {
namespace hdf {

//! Class for holding any HDF Value.
class Value {
public:
	Value()
		: val(0), type(Type::Unknown)
	{
	}

	Value(bool b)
		: val(b), type(Type::Boolean)
	{
	}

	Value(i32 i)
		: val(i), type(Type::Integer)
	{
	}

	Value(f64 f)
		: val(f), type(Type::Float)
	{
	}

	Value(std::string s)
		: val(s), type(Type::String)
	{
	}

	Value(Vector3d<f32> v3)
		: val(v3), type(Type::Vector3d)
	{
	}

	Value& operator = (const Value& other)
	{
		type = other.type;
		val = other.val;
	}

	bool get(bool& v)
	{
		if(type == Type::Boolean) {
			v = val.b_;
			return true;
		}
		
		return false;
	}
	
	bool get(i32& v)
	{
		if(type == Type::Integer) {
			v = val.i_;
			return true;
		}
		
		return false;
	}
	
	bool get(f64& v)
	{
		if(type == Type::Float) {
			v = val.f_;
			return true;
		}
		
		return false;
	}
	
	bool get(std::string& v)
	{
		if(type == Type::String) {
			// (std::string::value_type *)
			v = std::string(val.str.ptr,val.str.length);
			return true;
		}
		
		return false;
	}
	
	bool get(Vector3d<f32>& v) const
	{
		if(type == Type::Vector3d) {
			v[0] = val.v3_[0];
			v[1] = val.v3_[1];
			v[2] = val.v3_[2];
			return true;
		}

		return false;
	}
	
	bool set(const bool v)
	{
		if(type == Type::Boolean) {
			val.b_ = v;
			return true;
		}
		
		return false;
	}
	
	bool set(const i32 v)
	{
		if(type == Type::Integer) {
			val.i_ = v;
			return true;
		}
		
		return false;
	}
	
	bool set(const f64 v)
	{
		if(type == Type::Float) {
			val.f_ = v;
			return true;
		}
		
		return false;
	}
	
	bool set(const std::string v)
	{
		if(type == Type::String) {
			delete[] val.str.ptr;
			val.str.length = v.size();
			val.str.ptr = new char[val.str.length];
			memcpy((void*)(val.str.ptr), v.data(), val.str.length);
			return true;
		}
		
		return false;
	}
	
	bool set(const Vector3d<f32> v)
	{
		if(type == Type::Vector3d) {
			val.v3_[0] = v[0];
			val.v3_[1] = v[1];
			val.v3_[2] = v[2];
			return true;
		}
		
		return false;
	}

	void reset()
	{
		switch(type) {
			case Type::String:
				delete[] val.str.ptr;
				val.str.length = 0;
			default:
				break;
		}

		type = Type::Unknown;
	}

private:
	hdf::Type type;
	// todo: replace it with soething like boost::variant
	// (only custom-written)
	union HdfValue {
		~HdfValue()
		{	}
		HdfValue(bool b)
			: b_(b)
		{	}
		HdfValue(i32 i)
			: i_(i)
		{	}
		HdfValue(f64 f)
			: f_(f)
		{	}
		HdfValue(std::string const& s)
		{
			str.length = s.size();
			str.ptr = new char[str.length];
			memcpy((void*)(str.ptr), s.data(), str.length);
		}
		HdfValue(Vector3d<f32> v3)
		{
			v3_[0] = v3[0];
			v3_[1] = v3[1];
			v3_[2] = v3[2];
		}
		f32 v3_[3];
		struct string {
			char const* ptr;
			size_t length;
		} str;

		bool b_;
		i32 i_;
		f64 f_;
	} val;
};

} // namespace hdf
} // namespace hrengin

#endif//_hrengin_hdf_value_
