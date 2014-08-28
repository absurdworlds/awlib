#ifndef _hrengin_IModelParser_H_
#define _hrengin_IModelParser_H_

#include <hrengin/core/hrenginmodels.h>
#include <hrengin/core/IFileParser.h>

namespace hrengin {
namespace filesystem {

class IReadFile;

class IModelParser : public IFileParser
{
public:
	virtual bool validate(IReadFile& file);
	virtual bool parse(IReadFile& file);

};


}
}


#endif//__HRENGIN_FILESYSTEM_IModelParser_H__