#ifndef __HRENGIN_CModelMaker_H__
#define __HRENGIN_CModelMaker_H__

#include <hrengin/core/IModelMaker.h>

namespace hrengin {

class IModel;

class CModelMaker : public IModelMaker
{
	virtual IModel* loadModel(const char* filename);

	void parseHndf(filesystem::IReadFile* file, IModel* model);
};

}

#endif//__HRENGIN_CModelMaker_H__