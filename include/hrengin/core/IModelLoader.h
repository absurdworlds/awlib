/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IModelLoader_
#define _hrengin_IModelLoader_

#include <hrengin/core/core.h>

namespace hrengin {
class IModel;

class IModelLoader {
public:
	virtual ~IModelLoader() {};
	virtual IModel* loadModel(const char* filename) = 0;
};

HR_CORE_EXP IModelLoader* createModelLoader();

} // namespace hrengin
#endif//_hrengin_IModelLoader_
