#ifndef __HRENGIN_IModelMaker_H__
#define __HRENGIN_IModelMaker_H__


namespace hrengin {

class IModel;

class IModelMaker
{
	virtual IModel* loadModel(const char* filename) = 0;
};

}

#endif//__HRENGIN_IModelMaker_H__