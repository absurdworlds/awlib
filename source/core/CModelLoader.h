/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CModelLoader_
#define _hrengin_CModelLoader_
#include <string>

#include <hrengin/core/IModelLoader.h>

namespace hrengin {
class IModel;

namespace io {
class IHDFParser;
}

namespace core {
class CModelLoader : public IModelLoader {
public:
	virtual IModel* loadModel (char const* filename);

private:
	bool hdfParse (hdf::IHDFParser* hdf, IModel* model);
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_CModelLoader_
