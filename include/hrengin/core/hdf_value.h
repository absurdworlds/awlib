#ifndef _hrengin_hdf_value_
#define _hrengin_hdf_value_

#include <string>

#include <hrengin/common/PodString.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace hdf {

enum class Type {
	Integer,
	Float,
	Boolean,
	String,
	Vector2d,
	Vector3d,
	Unknown
};

enum HdfType {
	HDF_INTEGER,
	HDF_FLOAT,
	HDF_BOOLEAN,
	HDF_STRING,
	HDF_VECTOR2,
	HDF_VECTOR3,
	HDF_UNKNOWN_TYPE
};
/*
   Class for holding any HDF Value.
   As soon as it is initialized, it's type is immutable.
 */
class Value {
public:
	Value()
		: val(0), type(HDF_UNKNOWN_TYPE)
	{	}

	Value(bool b)
		: val(b), type(HDF_BOOLEAN)
	{	}
	Value(i32 i)
		: val(i), type(HDF_INTEGER)
	{	}
	Value(f64 f)
		: val(f), type(HDF_FLOAT)
	{	}
	Value(std::string s)
		: val(s), type(HDF_STRING)
	{	}
	Value(Vector3d<f32> v3)
		: val(v3), type(HDF_VECTOR3)
	{	}

	bool get(bool& v)
	{
		if(type == HDF_BOOLEAN) {
			v = val.b_;
		}
		
		return false;
	}
	
	bool get(i32& v)
	{
		if(type == HDF_INTEGER) {
			v = val.i_;
		}
		
		return false;
	}
	
	bool get(f64& v)
	{
		if(type == HDF_FLOAT) {
			v = val.f_;
		}
		
		return false;
	}
	
	bool get(std::string& v)
	{
		if(type == HDF_STRING) {
			// (std::string::value_type *)
			v = std::string(val.s_.data,val.s_.length);
		}
		
		return false;
	}
	
	bool get(Vector3d<f32>& v)
	{
		if(type == HDF_VECTOR3) {
			v.X = val.v3_[0];
			v.Y = val.v3_[1];
			v.Z = val.v3_[2];
		}
	}
	
	bool set(const bool v)
	{
		if(type == HDF_BOOLEAN) {
			val.b_ = v;
			return true;
		}
		
		return false;
	}
	
	bool set(const i32 v)
	{
		if(type == HDF_INTEGER) {
			val.i_ = v;
			return true;
		}
		
		return false;
	}
	
	bool set(const f64 v)
	{
		if(type == HDF_FLOAT) {
			val.f_ = v;
			return true;
		}
		
		return false;
	}
	
	bool set(const std::string v)
	{
		if(type == HDF_STRING) {
			val.s_ = createPodString(v);
			return true;
		}
		
		return false;
	}
	
	bool set(const Vector3d<f32> v)
	{
		if(type == HDF_VECTOR3) {
			val.v3_[0] = v.X;
			val.v3_[1] = v.Y;
			val.v3_[2] = v.Z;
			return true;
		}
		
		return false;
	}

	const HdfType type;
private:
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
