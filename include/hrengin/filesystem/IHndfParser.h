#ifndef __HRENGIN_FILESYSTEM_IHndfParser_H__
#define __HRENGIN_FILESYSTEM_IHndfParser_H__

#include <string>

namespace hrengin {
namespace io {

class IReadFile;

enum HndfObjectType {
		HNDF_NODE,
		HNDF_VARIABLE
};

class IHndfParser
{
public:
	virtual bool readObject();
	virtual void skipObject();
	virtual HndfObjectType getObjectType();
	virtual std::string getObjectName();

	virtual std::string getStringValue();
	virtual float getFloatValue();
	virtual int getIntegerValue();
	virtual bool getBooleanValue();

	virtual void addError(std::string error);
};

IHndfParser* createHndfParser(IReadFile* file);


}
}


#endif//__HRENGIN_FILESYSTEM_IHndfParser_H__