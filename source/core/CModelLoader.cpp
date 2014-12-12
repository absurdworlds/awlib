/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <fstream>

#include <hrengin/core/models.h>
#include <hrengin/core/paths.h>
#include <hrengin/common/stringutils.h>

#include <hrengin/core/IFileSystem.h>

#include <hrengin/hdf/IHDFParser.h>

#include <hrengin/core/IModel.h>

#include "CModelLoader.h"

namespace hrengin {

bool hndfParseNode(hdf::IHDFParser* hdf, IModel* model, std::string curNode);
bool hndfParseObject(hdf::IHDFParser* hndf, IModel* model, std::string curNode);
bool hndfParseShapeNode(hdf::IHDFParser* hndf, IModel* model);

IModelLoader* createModelLoader()
{
	return new CModelLoader();
}

IModel* CModelLoader::loadModel(char const* filename)
{
	std::string path = io::modelpath + filename;
	std::string ext;

	std::ifstream file;
	file.open(path, std::ios::binary);

	if (file.fail()) {
		return 0;
	}
	
	IModel* model = new IModel; // temp

	getFileExtension(ext, filename);

	if(ext == "hndf" || ext == "hdf") {
		hdf::IHDFParser* hdf = hdf::createHDFParser(file);

		hdfParse(hdf, model);

		delete hdf;
	}

	return model;
}

bool CModelLoader::hdfParse(hdf::IHDFParser* hdf, IModel* model)
{
	std::string curNode;

	hdf->read();
	if(hdf->getObjectType() != hdf::HDF_OBJ_NODE) {
		return false;
	}

	hdf->getObjectName(curNode);

	return hndfParseNode(hdf, model, curNode);
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

bool hndfParseNode(hdf::IHDFParser* hndf, IModel* model, std::string curNode)
{
	bool successful = true;

	while(hndf->read()) {
		successful = hndfParseObject(hndf, model, curNode);
	}

	return successful;
}

bool hndfParseObject(hdf::IHDFParser* hndf, IModel* model, std::string curNode)
{
	bool successful = true;
	hdf::HdfObjectType type = hndf->getObjectType();
	std::string objectName;

	switch(type) {
	case hdf::HDF_OBJ_NODE:
		hndf->getObjectName(objectName);

		if(objectName == "shapes") {
			if(curNode != "model") {
				hndf->error(hdf::HDF_LOG_ERROR, "'shapes' node must be inside a 'model' node");
				return false;
			} else {
				successful = hndfParseNode(hndf, model, objectName);
			}
		} else if((curNode == "shapes") && (objectName == "*" || objectName == "shape")) {
			successful = hndfParseShapeNode(hndf, model);
		} else {
			hndf->error(hdf::HDF_LOG_ERROR, "found unknown node");
			hndf->skipNode();
		}
		break;
	case hdf::HDF_OBJ_VAL:
		hndf->skipValue();
		break;
	case hdf::HDF_OBJ_NODE_END:
		break;
	default:
		return false;
		
	//case io::HNDF_NODE_END:
		//endreached = true;
	}

	return successful;
}

bool hndfParseShapeNode(hdf::IHDFParser* hndf, IModel* model)
{
	hrengin::Primitive primitive;
	//io::HdfObjectType type = hndf->getObjectType();


	while(hndf->read()) {
		hdf::HdfObjectType type = hndf->getObjectType();

		if(type == hdf::HDF_OBJ_NODE_END) {
			break;
		}
		if(type != hdf::HDF_OBJ_VAL) {
			hndf->error(hdf::HDF_LOG_ERROR, "expected a variable in a 'shape' node, got node");
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
			} else if(type == "plane") {
				primitive.shape = SHAPE_PLANE;
			} else {
				hndf->error(hdf::HDF_LOG_ERROR, "unknown 'type' value");
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
			Vector3d<f32> vec3;
			hndf->readVector3d(vec3);
			
			primitive.rotation[0] = vec3[0];
			primitive.rotation[1] = vec3[1];
			primitive.rotation[2] = vec3[2];
		} else if(objectName == "offset") {
			Vector3d<f32> vec3;
			hndf->readVector3d(vec3);
			
			primitive.offset[0] = vec3[0];
			primitive.offset[1] = vec3[1];
			primitive.offset[2] = vec3[2];
		} else {
			hndf->skipValue();
		}
	}

	model->primitives.push_back(primitive);

	return true;
}

} // namespace hrengin
