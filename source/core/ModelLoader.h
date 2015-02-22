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
#include <string>

#include <hrengin/core/ModelLoader.h>

namespace hrengin {
class Model;

namespace io {
class HDFParser;
}

namespace core {
class ModelLoader : public ModelLoader {
public:
	virtual Model* loadModel (char const* filename);

private:
	bool hdfParse (hdf::HDFParser* hdf, Model* model);
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_ModelLoader_
