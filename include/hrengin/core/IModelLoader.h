#ifndef __HRENGIN_IModelLoaderr_H__
#define __HRENGIN_IModelLoaderr_H__

#include <hrengin/common/hrenginapi.h>

namespace hrengin {

class IModel;

class IModelLoader
{
public:
	virtual IModel* loadModel(const char* filename) = 0;
};

HRENGIN_API IModelLoader* createModelLoader();

} //end namespace hrengin


#endif//__HRENGIN_IModelLoader_H__