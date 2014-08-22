#ifndef __HRENGIN_FILESYSTEM_IHndfParser_H__
#define __HRENGIN_FILESYSTEM_IHndfParser_H__

#include <hrengin/common/hrenginapi.h>

#include <hrengin/common/Vector3d.h>

#include <string>

namespace hrengin {
namespace io {

class IReadFile;

enum HdfObjectType {
	HDF_OBJ_NULL = 0,
	HDF_OBJ_NODE,
	HDF_OBJ_NODE_END,
	HDF_OBJ_VAL,
	HDF_OBJ_CMD
};

	
enum HdfParserMessage {
	HDF_ERR_NOTICE,
	HDF_ERR_WARNING,
	HDF_ERR_ERROR
};

class IHndfParser
{
public:
	virtual bool read() = 0;
	virtual HdfObjectType getObjectType() = 0;
	virtual void getObjectName(std::string& name) = 0;

	virtual void readFloat(float& val) = 0;
	virtual void readFloat(double& val) = 0;
	virtual void readInt(u32& val) = 0;
	virtual void readInt(i32& val) = 0;
	virtual void readBool(bool& val) = 0;
	virtual void readString(std::string& val) = 0;
	virtual void readVector3d(Vector3d& val) = 0;

	virtual void skipValue() = 0;
	virtual void skipNode() = 0;

	virtual void error(HdfParserMessage type, std::string msg) = 0;
};

HRENGINFILESYSTEM_API IHndfParser* createHndfParser(IReadFile* file);


}
}


#endif//__HRENGIN_FILESYSTEM_IHndfParser_H__