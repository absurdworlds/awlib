
#include <hrengin/core/hrenginmodels.h>
#include <hrengin/filesystem/hrenginpaths.h>
#include <hrengin/filesystem/hrenginfsutil.h>
#include <hrengin/filesystem/IFileSystem.h>
#include <hrengin/filesystem/IReadFile.h>
#include <hrengin/filesystem/IHndfParser.h>

#include <hrengin/core/IModel.h>

#include  "CModelLoader.h"

namespace hrengin {

IModel* CModelLoader::loadModel(const char* filename)
{
	std::string path = io::modelpath + filename;
	std::string ext;

	io::IReadFile* file = io::openReadFile(path);

	if (!file) {
		return 0;
	}
	
	IModel* model = new IModel; // temp

	io::getFileExtension(ext, filename);

	if(ext == "hndf" || ext == "ndf") {
		hndfParse(file, model);
	}
}

bool CModelLoader::hndfParse(io::IReadFile* file, IModel* model)
{
	//EHndfNodeType nodeType;

	io::IHndfParser* hndf = io::createHndfParser(file);
	
	if(!hndf) {
		return false;
	}

	hndf->readObject();

	hndfParseNode(hndf,model);
}

bool CModelLoader::hndfParseNode(io::IHndfParser* hndf, IModel* model)
{
	bool successful = true;
	std::string curNode = hndf->getObjectName();
	//bool endreached = false;
	while(hndf->readObject()) {
		successful = hndfParseObject(hndf, model, curNode)
	}

	return successful;
}

bool CModelLoader::hndfParseObject(io::IHndfParser* hndf, IModel* model, std::string curNode)
{
	bool successful = true;
	std::string objectName = hndf->getObjectName();
	switch(hndf->getObjectType()) {
	case io::HNDF_NODE:
		if(objectName == "shapes") {
			if(curNode != "model") {
				hndf->addError("'shapes' node must be inside a 'model' node");
				return false;
			} else {
				successful = hndfParseNode(hndf, model);
			}
		} else if((curNode == "shapes") && (objectName == "*" || objectName == "shape")) {
			successful = hndfParseShapeNode(hndf, model);
		} else {
			hndf->addError("found unknown node");
			hndf->skipObject();
		}
		break;
	case io::HNDF_VARIABLE:
		hndf->skipObject();
		break;
		
	//case io::HNDF_NODE_END:
		//endreached = true;
	}

	return successful;
}

bool CModelLoader::hndfParseShapeNode(io::IHndfParser* hndf, IModel* model)
{
	std::string curNode = hndf->getObjectName();
	//bool endreached = false;

	hrengin::SPrimititve primitive;

	while(hndf->readObject()) {
		if(hndf->getObjectType() != io::HNDF_VARIABLE) {
			hndf->addError("expected a variable in a 'shape' node, got node");
			return false; 
		}
		
		std::string objectName = hndf->getObjectName();

		if(objectName == "type") {
			std::string type = hndf->getStringValue();
			if(type == "sphere") {
				primitive.shape = SHAPE_SPHERE;
			} else if(type == "box") {
				primitive.shape = SHAPE_BOX;
			} else if(type == "capsule") {
				primitive.shape = SHAPE_CAPSULE;
			} else if(type == "cylinder") {
				primitive.shape = SHAPE_CYLINDER;
			} else if(type == "cone") {
				primitive.shape = SHAPE_CONE;
			} else {
				hndf->addError("unknown 'type' value");
				return false;
			}
		} else if(objectName == "radius" || objectName == "width") {
			primitive.dimensions[0] = hndf->getFloatValue();
		} else if(objectName == "height") {
			primitive.dimensions[1] = hndf->getFloatValue();
		} else if(objectName == "length") {
			primitive.dimensions[2] = hndf->getFloatValue();
		} else if(objectName == "rotation") {
			primitive.rotation[0] = hndf->getFloatValue();
			primitive.rotation[1] = hndf->getFloatValue();
			primitive.rotation[2] = hndf->getFloatValue();
		} else {
			hndf->skipObject();
		}
	}
}
}

/*
[model
	[shape
		type=capsule
		height=float:8.911
		radius=float:1.997
		rotaion=float:0.0 0.0 90.0
	]
]	
	*/
}