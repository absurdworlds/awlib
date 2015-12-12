/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/core/paths.h>
#include <aw/utility/string/string.h>

#include <aw/io/ReadFile.h>
#include <aw/io/BufferedStream.h>

#include <aw/hdf/Parser.h>

#include <aw/core/Model.h>

#include "ModelLoader.h"

namespace aw {
namespace core {

ModelLoader* createModelLoader ()
{
	return new impl_::ModelLoader();
}

namespace impl_ {
bool hdfParseNode(hdf::Parser* hdf, Model* model, std::string curNode);
bool hdfParseObject(hdf::Parser* hdf, Model* model, std::string curNode);
bool hdfParseShapeNode(hdf::Parser* hdf, Model* model);

Model* ModelLoader::loadModel (char const* filename)
{
	std::string path = io::modelpath + filename;
	std::string ext;

	io::ReadFile file(path);

	if (!file.isOpen()) {
		return 0;
	}

	Model* model = new Model; // FIXME: Should be allocated on stack

	getFileExtension(ext, filename);

	if(ext == "hndf" || ext == "hdf") {
		io::CharacterStream* stream = io::createBufferedStream(file);
		hdf::Parser* hdf = hdf::createParser(stream);

		hdfParse(hdf, model);

		delete hdf;
		delete stream;
	}

	return model;
}

bool ModelLoader::hdfParse (hdf::Parser* hdf, Model* model)
{
	std::string curNode;

	hdf->read();
	if(hdf->getObjectType() != hdf::HDF_OBJ_NODE) {
		return false;
	}

	hdf->getObjectName(curNode);

	return hdfParseNode(hdf, model, curNode);
}

bool hdfParseNode(hdf::Parser* hdf, Model* model, std::string curNode)
{
	bool successful = true;

	while(hdf->read()) {
		successful = hdfParseObject(hdf, model, curNode);
	}

	return successful;
}

// FIXME mess of nested if's
bool hdfParseObject(hdf::Parser* hdf, Model* model, std::string curNode)
{
	bool successful = true;
	hdf::ObjectType type = hdf->getObjectType();
	std::string objectName;

	switch(type) {
	case hdf::HDF_OBJ_NODE:
		hdf->getObjectName(objectName);

		if(objectName == "shapes") {
			if(curNode != "model") {
				hdf->error(hdf::HDF_LOG_ERROR, "'shapes' node must be inside a 'model' node");
				return false;
			} else {
				successful = hdfParseNode(hdf, model, objectName);
			}
		} else if ((curNode == "shapes")
			&& (objectName == "*" || objectName == "shape")) {
			successful = hdfParseShapeNode(hdf, model);
		} else {
			hdf->error(hdf::HDF_LOG_ERROR, "found unknown node");
			hdf->skipNode();
		}
		break;
	case hdf::HDF_OBJ_VAL:
		hdf->skipValue();
		break;
	case hdf::HDF_OBJ_NODE_END:
		break;
	default:
		return false;
	}

	return successful;
}

bool hdfParseShapeNode(hdf::Parser* hdf, Model* model)
{
	aw::Primitive primitive;
	//io::ObjectType type = hdf->getObjectType();


	while(hdf->read()) {
		hdf::ObjectType type = hdf->getObjectType();

		if(type == hdf::HDF_OBJ_NODE_END) {
			break;
		}
		if(type != hdf::HDF_OBJ_VAL) {
			hdf->error(hdf::HDF_LOG_ERROR, "expected a variable in a 'shape' node, got node");
			return false; 
		}

		std::string objectName;

		hdf->getObjectName(objectName);

		if(objectName == "type") {
			std::string type;
			hdf->readString(type);
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
				hdf->error(hdf::HDF_LOG_ERROR, "unknown 'type' value");
				return false;
			}
		} else if(objectName == "direction") {
			std::string axis;
			hdf->readString(axis);
			if(axis == "axisX" || axis == "axisx" || axis == "x" || axis == "X") {
				primitive.axis = AXIS_X;
			} else if(axis == "axisZ" || axis == "axisz" || axis == "z" || axis == "Z") {
				primitive.axis = AXIS_Z;
			} else {
				primitive.axis = AXIS_Y;
			}

		} else if(objectName == "radius" || objectName == "width") {
			hdf->readFloat(primitive.dimensions[0]);
		} else if(objectName == "height") {
			hdf->readFloat(primitive.dimensions[1]);
		} else if(objectName == "length") {
			hdf->readFloat(primitive.dimensions[2]);
		} else if(objectName == "rotation") {
			Vector3d<f32> vec3;
			hdf->readVector3d(vec3);

			primitive.rotation[0] = vec3[0];
			primitive.rotation[1] = vec3[1];
			primitive.rotation[2] = vec3[2];
		} else if(objectName == "offset") {
			Vector3d<f32> vec3;
			hdf->readVector3d(vec3);

			primitive.offset[0] = vec3[0];
			primitive.offset[1] = vec3[1];
			primitive.offset[2] = vec3[2];
		} else {
			hdf->skipValue();
		}
	}

	model->primitives.push_back(primitive);

	return true;
}
} // namespace impl_
} // namespace core
} // namespace aw
