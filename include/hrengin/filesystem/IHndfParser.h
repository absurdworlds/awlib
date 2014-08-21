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
	virtual bool read() = 0;
	virtual HdfObjectType getObjectType() = 0;
	virtual void getObjectName(std::string& name) = 0;
	
	template<typename T> 
	void readValue(T& val);
	
	virtual void skipObject() = 0;

	//virtual void addError(std::string error) = 0;
};

HRENGINFILESYSTEM_API IHndfParser* createHndfParser(IReadFile* file);


}
}


#endif//__HRENGIN_FILESYSTEM_IHndfParser_H__