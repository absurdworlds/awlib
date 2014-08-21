
#include <hrengin/core/hrenginmodels.h>
#include <hrengin/filesystem/hrenginpaths.h>
#include <hrengin/filesystem/hrenginfsutil.h>
#include <hrengin/filesystem/IFileSystem.h>
#include <hrengin/filesystem/IReadFile.h>
#include <hrengin/filesystem/IHndfParser.h>

#include <hrengin/core/IModel.h>

#include  "CModelLoader.h"

namespace hrengin {

IModelLoader* createModelLoader()
{
	return new CModelLoader();
}

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
	
		io::IHndfParser* hndf = io::createHndfParser(file);
	
		if(!hndf) {
			return false;
		}
		hndfParse(file, model);
	}

	delete file;

	return model;
}

bool CModelLoader::hndfParse(io::IHndfParser* hndf, IModel* model)
{
	std::string curNode;

	hndf->read();
	if(hndf->getObjectType() != io::HDF_OBJ_NODE) {
		return false;
	}

	
	return hndfParseNode(hndf, model);
}

#if 0
	while(hndf->read()) {
		switch(hndf->getObjectType()) {
		case io::HDF_OBJ_NODE:
			return hndfParseNode(hndf, model);
			break;
		/*case io::HDF_OBJ_VAL:
			break;*/
		default:
			return false;
		}
	}
#endif

bool CModelLoader::hndfParseNode(io::IHndfParser* hndf, IModel* model)
{
	bool successful = true;
	std::string curNode;

	hndf->getObjectName(curNode);
	
	while(hndf->read()) {
		successful = hndfParseObject(hndf, model, curNode);
	}

	return successful;
}

bool CModelLoader::hndfParseObject(io::IHndfParser* hndf, IModel* model, std::string curNode)
{
	bool successful = true;
	io::HdfObjectType type = hndf->getObjectType();
	std::string objectName;

	hndf->getObjectName(objectName);

	switch(type) {
	case io::HDF_OBJ_NODE:
		if(objectName == "shapes") {
			if(curNode != "model") {
				hndf->error(io::HDF_ERR_ERROR, "'shapes' node must be inside a 'model' node");
				return false;
			} else {
				successful = hndfParseNode(hndf, model);
			}
		} else if((curNode == "shapes") && (objectName == "*" || objectName == "shape")) {
			successful = hndfParseShapeNode(hndf, model);
		} else {
			hndf->error(io::HDF_ERR_ERROR, "found unknown node");
			hndf->skipObject();
		}
		break;
	case io::HDF_OBJ_VAL:
		hndf->skipObject();
		break;
	default:
		return false;
		
	//case io::HNDF_NODE_END:
		//endreached = true;
	}

	return successful;
}

bool CModelLoader::hndfParseShapeNode(io::IHndfParser* hndf, IModel* model)
{
	hrengin::SPrimitive primitive;
	io::HdfObjectType type = hndf->getObjectType();


	while(hndf->read()) {
		if(hndf->getObjectType() != io::HDF_OBJ_VAL) {
			hndf->error(io::HDF_ERR_ERROR, "expected a variable in a 'shape' node, got node");
			return false; 
		}
		
		std::string objectName;

		hndf->getObjectName(objectName);

		if(objectName == "type") {
			std::string type;
			hndf->readValue<std::string>(type);
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
				hndf->error(io::HDF_ERR_ERROR, "unknown 'type' value");
				return false;
			}
		} else if(objectName == "direction") {
			std::string axis;
			hndf->readValue<std::string>(axis);
			if(axis == "axisX" || axis == "axisx") {
				primitive.axis = AXIS_X;
			} else if(axis == "axisZ" || axis == "axisz") {
				primitive.axis = AXIS_Z;
			} else {
				primitive.axis = AXIS_Y;
			}
			printf("%s", axis.c_str());
		} else if(objectName == "radius" || objectName == "width") {
			hndf->readValue<float>(primitive.dimensions[0]);
		} else if(objectName == "height") {
			hndf->readValue<float>(primitive.dimensions[1]);
		} else if(objectName == "length") {
			hndf->readValue<float>(primitive.dimensions[2]);
		} else if(objectName == "rotation") {
			hrengin::Vector3d vec3;
			hndf->readValue<Vector3d>(vec3);
			
			primitive.rotation[0] = vec3.X;
			primitive.rotation[1] = vec3.Y;
			primitive.rotation[2] = vec3.Z;
		} else {
			hndf->skipObject();
		}
	}

	model->primitives.push_back(primitive);

	return true;
}
}