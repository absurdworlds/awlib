#ifndef _hrengin_CModelLoader_
#define _hrengin_CModelLoader_

#include <string>

#include <hrengin/core/IModelLoader.h>

namespace hrengin {

class IModel;

namespace io {
	class IHDFParser;
}

class CModelLoader : public IModelLoader
{
public:
	virtual IModel* loadModel(const char* filename);

private:
	bool hndfParse(io::IHDFParser* hndf, IModel* model);
	//bool hndfParseNode(io::IHDFParser* hndf, IModel* model);
	//bool hndfParseObject(io::IHDFParser* hndf, IModel* model, std::string curNode);
	//bool hndfParseShapeNode(io::IHDFParser* hndf, IModel* model);
};

}

#endif//_hrengin_CModelLoader_