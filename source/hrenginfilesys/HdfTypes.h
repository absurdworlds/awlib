#ifndef _hrengin_HdfTypes_h_
#define _hrengin_HdfTypes_h_

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector2d.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {

enum HdfType {
	HDF_INTEGER,
	HDF_FLOAT,
	HDF_BOOLEAN,
	HDF_STRING,
	HDF_VECTOR2,
	HDF_VECTOR3
};

struct HdfToken {

};

template<typename T>
bool isValidHdfType(HdfType type)
{
	return false;
}

template<typename T>
bool isValidHdfType(HdfType type, typename std::enable_if<std::is_integral<T>::value,T>::type* t = 0) {
	return HDF_INTEGER == type;
}

template<typename T>
bool isValidHdfType(HdfType type, typename std::enable_if<std::is_floating_point<T>::value,T>::type* t = 0) {
	return HDF_FLOAT == type;
}


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

} // namespace hrengin

#endif //_hrengin_HdfTypes_h_