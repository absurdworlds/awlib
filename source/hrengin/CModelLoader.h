#ifndef __HRENGIN_CModelLoader_H__
#define __HRENGIN_CModelLoader_H__

#include <string>

#include <hrengin/core/IModelLoader.h>

namespace hrengin {

class IModel;

namespace io {
	class IHndfParser;
}

class CModelLoader : public IModelLoader
{
public:
	virtual IModel* loadModel(const char* filename);

private:
	bool hndfParse(io::IReadFile* file, IModel* model);
	bool hndfParseNode(io::IHndfParser* hndf, IModel* model);
	bool hndfParseObject(io::IHndfParser* hndf, IModel* model, std::string curNode);
	bool hndfParseShapeNode(io::IHndfParser* hndf, IModel* model);
};

}

#endif//__HRENGIN_CModelLoader_H__