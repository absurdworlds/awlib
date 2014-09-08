#ifndef _hrengin_hdf_value_
#define _hrengin_hdf_value_

#include <string>

#include <hrengin/common/PodString.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/types.h>

#include <hrengin/core/hdf_shared.h>

namespace hrengin {
namespace hdf {
/*
   Class for holding any HDF Value.
 */
class Value {
public:
	Value()
		: val(0), type(Type::Unknown)
	{	}

	Value(bool b)
		: val(b), type(Type::Boolean)
	{	}
	Value(i32 i)
		: val(i), type(Type::Integer)
	{	}
	Value(f64 f)
		: val(f), type(Type::Float)
	{	}
	Value(std::string s)
		: val(s), type(Type::String)
	{	}
	Value(Vector3d<f32> v3)
		: val(v3), type(Type::Vector3d)
	{	}

	Value& operator = (const Value& other)
	{
		type = other.type;
		val = other.val;
	}

	bool get(bool& v)
	{
		if(type == Type::Boolean) {
			v = val.b_;
		}
		
		return false;
	}
	
	bool get(i32& v)
	{
		if(type == Type::Integer) {
			v = val.i_;
		}
		
		return false;
	}
	
	bool get(f64& v)
	{
		if(type == Type::Float) {
			v = val.f_;
		}
		
		return false;
	}
	
	bool get(std::string& v)
	{
		if(type == Type::String) {
			// (std::string::value_type *)
			v = std::string(val.s_.data,val.s_.length);
		}
		
		return false;
	}
	
	bool get(Vector3d<f32>& v)
	{
		if(type == Type::Vector3d) {
			v.X = val.v3_[0];
			v.Y = val.v3_[1];
			v.Z = val.v3_[2];
		}
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
			val.s_ = createPodString(v);
			return true;
		}
		
		return false;
	}
	
	bool set(const Vector3d<f32> v)
	{
		if(type == Type::Vector3d) {
			val.v3_[0] = v.X;
			val.v3_[1] = v.Y;
			val.v3_[2] = v.Z;
			return true;
		}
		
		return false;
	}

private:
	hdf::Type type;
	union HdfValue {
		HdfValue(bool b)
			: b_(b)
		{	}
		HdfValue(i32 i)
			: i_(i)
		{	}
		HdfValue(f64 f)
			: f_(f)
		{	}
		~HdfValue() 
		{	}
#if 0
		HdfValue(std::string s)
			: s_(s)
		{	}
		HdfValue(Vector3d<f32> v3)
			: v3_(v3)
		{	}
		Vector3d<f32> v3_;
		std::string s_;
#else
		HdfValue(std::string s)
			: s_(createPodString(s))
		{	}
		HdfValue(Vector3d<f32> v3)
		{
			v3_[0] = v3.X;
			v3_[1] = v3.Y;
			v3_[2] = v3.Z;
		}
		f32 v3_[3];
		PodString s_;
#endif
		bool b_;
		i32 i_;
		f64 f_;
	} val;
};

} // namespace hdf
} // namespace hrengin

#endif//_hrengin_hdf_value_
