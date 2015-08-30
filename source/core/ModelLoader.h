/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_ModelLoader_impl_
#define _awrts_ModelLoader_impl_
#include <string>

#include <awrts/core/ModelLoader.h>

namespace awrts {
class Model;

namespace io {
class HDFParser;
}

namespace core {
namespace impl_ {
class ModelLoader : public core::ModelLoader {
public:
	virtual Model* loadModel (char const* filename);

private:
	bool hdfParse (hdf::HDFParser* hdf, Model* model);
};

} // namespace impl_
} // namespace core
} // namespace awrts
#endif//_awrts_ModelLoader_impl_
