
#include <hrengin/core/hrenginmodels.h>
#include <hrengin/filesystem/hrenginpaths.h>
#include <hrengin/filesystem/hrenginfsutil.h>
#include <hrengin/filesystem/IFileSystem.h>
#include <hrengin/filesystem/IReadFile.h>
#include <hrengin/filesystem/IHndfParser.h>

#include <hrengin/core/IModel.h>

#include  "CModelLoader.h"

namespace hrengin {

bool hndfParseNode(io::IHndfParser* hndf, IModel* model, std::string curNode);
bool hndfParseObject(io::IHndfParser* hndf, IModel* model, std::string curNode);
bool hndfParseShapeNode(io::IHndfParser* hndf, IModel* model);

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

		hndfParse(hndf, model);

		delete hndf;
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

	hndf->getObjectName(curNode);

	return hndfParseNode(hndf, model, curNode);
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

bool hndfParseNode(io::IHndfParser* hndf, IModel* model, std::string curNode)
{
	bool successful = true;

	while(hndf->read()) {
		successful = hndfParseObject(hndf, model, curNode);
	}

	return successful;
}

bool hndfParseObject(io::IHndfParser* hndf, IModel* model, std::string curNode)
{
	bool successful = true;
	io::HdfObjectType type = hndf->getObjectType();
	std::string objectName;

	switch(type) {
	case io::HDF_OBJ_NODE:
		hndf->getObjectName(objectName);

		if(objectName == "shapes") {
			if(curNode != "model") {
				hndf->error(io::HDF_ERR_ERROR, "'shapes' node must be inside a 'model' node");
				return false;
			} else {
				successful = hndfParseNode(hndf, model, objectName);
			}
		} else if((curNode == "shapes") && (objectName == "*" || objectName == "shape")) {
			successful = hndfParseShapeNode(hndf, model);
		} else {
			hndf->error(io::HDF_ERR_ERROR, "found unknown node");
			hndf->skipNode();
		}
		break;
	case io::HDF_OBJ_VAL:
		hndf->skipValue();
		break;
	case io::HDF_OBJ_NODE_END:
		break;
	default:
		return false;
		
	//case io::HNDF_NODE_END:
		//endreached = true;
	}

	return successful;
}

bool hndfParseShapeNode(io::IHndfParser* hndf, IModel* model)
{
	hrengin::SPrimitive primitive;
	//io::HdfObjectType type = hndf->getObjectType();


	while(hndf->read()) {
		io::HdfObjectType type = hndf->getObjectType();

		if(type == io::HDF_OBJ_NODE_END) {
			break;
		}
		if(type != io::HDF_OBJ_VAL) {
			hndf->error(io::HDF_ERR_ERROR, "expected a variable in a 'shape' node, got node");
			return false; 
		}
		
		std::string objectName;

		hndf->getObjectName(objectName);

		if(objectName == "type") {
			std::string type;
			hndf->readString(type);
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
			hndf->readString(axis);
			if(axis == "axisX" || axis == "axisx" || axis == "x" || axis == "X") {
				primitive.axis = AXIS_X;
			} else if(axis == "axisZ" || axis == "axisz" || axis == "z" || axis == "Z") {
				primitive.axis = AXIS_Z;
			} else {
				primitive.axis = AXIS_Y;
			}

		} else if(objectName == "radius" || objectName == "width") {
			hndf->readFloat(primitive.dimensions[0]);
		} else if(objectName == "height") {
			hndf->readFloat(primitive.dimensions[1]);
		} else if(objectName == "length") {
			hndf->readFloat(primitive.dimensions[2]);
		} else if(objectName == "rotation") {
			hrengin::Vector3d vec3;
			hndf->readVector3d(vec3);
			
			primitive.rotation[0] = vec3.X;
			primitive.rotation[1] = vec3.Y;
			primitive.rotation[2] = vec3.Z;
		} else if(objectName == "offset") {
			hrengin::Vector3d vec3;
			hndf->readVector3d(vec3);
			
			primitive.offset[0] = vec3.X;
			primitive.offset[1] = vec3.Y;
			primitive.offset[2] = vec3.Z;
		} else {
			hndf->skipValue();
		}
	}

	model->primitives.push_back(primitive);

	return true;
}
}