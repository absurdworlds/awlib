#ifndef __HRENGIN_IModelLoaderr_H__
#define __HRENGIN_IModelLoaderr_H__


namespace hrengin {

class IModel;

class IModelLoader
{
	virtual IModel* loadModel(const char* filename) = 0;
};

}

#endif//__HRENGIN_IModelLoader_H__