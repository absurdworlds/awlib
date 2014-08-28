#ifndef _hrengin_IModelLoader_
#define _hrengin_IModelLoader_

#include <hrengin/common/api.h>

namespace hrengin {

class IModel;

class IModelLoader
{
public:
	virtual IModel* loadModel(const char* filename) = 0;
};

HRENGIN_API IModelLoader* createModelLoader();

} //end namespace hrengin


#endif//_hrengin_IModelLoader_