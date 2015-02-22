/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ModelLoader_
#define _hrengin_ModelLoader_
#include <hrengin/core/core.h>

namespace hrengin {
class Model;

namespace core {
//! Reads model files from disk and stores in hrengin standard format
class ModelLoader {
public:
	//! Virtual destructor
	virtual ~ModelLoader()
	{
	}

	/*! Load model from disk
	 * \see Model
	 */
	virtual Model* loadModel (char const* filename) = 0;
};

/*! Create a model loader
 * \note It is best to use only one model loader
 */
HR_CORE_EXP ModelLoader* createModelLoader();
} // namespace core
} // namespace hrengin
#endif//_hrengin_ModelLoader_
