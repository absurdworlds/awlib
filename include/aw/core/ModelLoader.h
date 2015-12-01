/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_ModelLoader_
#define _aw_ModelLoader_
#include <aw/core/core.h>

namespace aw {
class Model;

namespace core {
//! Interface for model loader
class ModelLoader {
public:
	//! Virtual destructor
	virtual ~ModelLoader()
	{
	}

	/*! Load model from disk
	 * \see Model
	 */
	virtual Model* loadModel(char const* filename) = 0;
};

//! Create a model loader
AW_CORE_EXP ModelLoader* createModelLoader();
} // namespace core
} // namespace aw
#endif//_aw_ModelLoader_
