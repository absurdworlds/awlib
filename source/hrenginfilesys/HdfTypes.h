#ifndef _hrengin_HdfTypes_h_
#define _hrengin_HdfTypes_h_

namespace hrengin {
namespace io {

enum HdfType {
	HDF_INTEGER,
	HDF_FLOAT,
	HDF_BOOLEAN,
	HDF_STRING,
	HDF_VECTOR2,
	HDF_VECTOR3,
	HDF_UNKNOWN_TYPE
};

template<typename T>
bool isValidHdfType(HdfType type)
{
	return false;
}

#if 0

template<typename T>
bool isValidHdfType(HdfType type, typename std::enable_if<std::is_integral<T>::value,T>::type* t = 0) {
	return HDF_INTEGER == type;
}

template<typename T>
bool isValidHdfType(HdfType type, typename std::enable_if<std::is_floating_point<T>::value,T>::type* t = 0) {
	return HDF_FLOAT == type;
}

#else

template<>
bool isValidHdfType<i32>(HdfType type) {
	return HDF_INTEGER == type;
}

template<>
bool isValidHdfType<u32>(HdfType type) {
	return HDF_INTEGER == type;
}

template<>
bool isValidHdfType<f32>(HdfType type) {
	return HDF_FLOAT == type;
}

template<>
bool isValidHdfType<f64>(HdfType type) {
	return HDF_FLOAT == type;
}
#endif

template<>
bool isValidHdfType<bool>(HdfType type) {
	return HDF_BOOLEAN == type;
}

template<>
bool isValidHdfType<std::string>(HdfType type) {
	return HDF_STRING == type;
}

template<>
bool isValidHdfType<Vector2d>(HdfType type) {
	return HDF_VECTOR2 == type;
}

template<>
bool isValidHdfType<Vector3d>(HdfType type) {
	return HDF_VECTOR3 == type;
}


HdfType hdfTokenToType(HdfToken token) 
{
	if(token.value == "bool" || token.value == "b") {
		return HDF_BOOLEAN;
	} else if(token.value == "int" || token.value == "i") {
		return HDF_INTEGER;
	} else if(token.value == "float" || token.value == "f") {
		return HDF_FLOAT;
	} else if(token.value == "vec3" || token.value == "v3") {
		return HDF_VECTOR3;
	} else if(token.value == "vec2" || token.value == "v2") {
		return HDF_VECTOR2;
	} else if(token.value == "string" || token.value == "s") {
		return HDF_STRING;
	} else {
		return HDF_UNKNOWN_TYPE;
	}
}

HdfType hdfConvertImpicitType(HdfToken token) 
{
	return HDF_UNKNOWN_TYPE;
}



} //namespace io
} // namespace hrengin

#endif //_hrengin_HdfTypes_h_