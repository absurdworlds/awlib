/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IModelLoader_
#define _hrengin_IModelLoader_
#include <hrengin/core/core.h>

namespace hrengin {
class IModel;

namespace core {
//! Reads model files from disk and stores in hrengin standard format
class IModelLoader {
public:
	//! Virtual destructor
	virtual ~IModelLoader()
	{
	}
	
	/*! Load model from disk
	 * \see IModel
	 */	
	virtual IModel* loadModel (char const* filename) = 0;
};

/*! Create a model loader
 * \note It is best to use only one model loader
 */
HR_CORE_EXP IModelLoader* createModelLoader();
} // namespace core
} // namespace hrengin
#endif//_hrengin_IModelLoader_
