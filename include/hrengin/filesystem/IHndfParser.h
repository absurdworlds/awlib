#ifndef __HRENGIN_FILESYSTEM_IHndfParser_H__
#define __HRENGIN_FILESYSTEM_IHndfParser_H__

#include <hrengin/common/hrenginapi.h>

#include <string>

namespace hrengin {
namespace io {

class IReadFile;

enum HdfObjectType {
	HDF_OBJ_NULL = 0,
	HDF_OBJ_NODE,
	HDF_OBJ_VAL,
	HDF_OBJ_CMD
};

class IHndfParser
{
public:
	virtual bool readObject() = 0;
	virtual void skipObject() = 0;
	virtual HdfObjectType getObjectType() = 0;
	virtual std::string getObjectName() = 0;

	virtual bool getStringValue(std::string& val) = 0;
	virtual bool getFloatValue(float& val) = 0;
	virtual bool getIntegerValue(int& val) = 0;
	virtual bool getBooleanValue(bool& val) = 0;

	virtual void addError(std::string error) = 0;
};

HRENGINFILESYSTEM_API IHndfParser* createHndfParser(IReadFile* file);


}
}


#endif//__HRENGIN_FILESYSTEM_IHndfParser_H__