
#include <string>

#include <hrengin/filesystem/hrenginpaths.h>
#include <hrengin/filesystem/hrenginfsutil.h>
#include <hrengin/filesystem/IFileSystem.h>
#include <hrengin/filesystem/IReadFile.h>

#include  "CModelMaker.h"

namespace hrengin {

IModel* CModelMaker::loadModel(const char* filename)
{
	std::string path = filesystem::modelpath + filename;
	std::string ext;

	filesystem::IReadFile* file = filesystem::openReadFile(path);

	if (!file) {
		return 0;
	}
	

	filesystem::getFileExtension(ext, filename);

	if(ext == "hndf" || ext == "ndf") {
		parseHndf(file);
	}
}

void CModelMaker::parseHndf(filesystem::IReadFile* file, IModel* model)
{
	EHndfNodeType nodeType;


	u32 state = 0;
	filesystem::IHndfParser* hndf = filesystem::createHndfParser(file);
	
	if(!hndf) {
		return -1;
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

	hndf->read();
	
	if(hndf->getNodeName() != "model") {
		return -2;
	}

	state = 1;

	while(hndf->readNode()) {
		switch(hndf->getDataType()) {
		case HNDF_NODE:
			if(hndf->getNodeName() == "shape") {
				if(state != 1) {
					return -3;
				}

				state = 2;
			}

			break;
		case HNDF_VARIBALE:
			if(state == 2) {
				if(hndf->getVarName() == "type") {
					if(hndf->getValue() == "capsule") {
						shape.shape = hrengin::SHAPE_CAPSULE;
					} else if(hndf->getValue() == "sphere") {
						shape.shape = hrengin::SHAPE_SPHERE;
					}
				} else if(hndf->getVarName() == "radius" || hndf->getVarName() == "width") {
					shape.dimensions[0] = hndf->getFloatValue();
				} else if(hndf->getVarName() == "height") {
					shape.dimensions[1] = hndf->getFloatValue();
				} else if(hndf->getVarName() == "length") {
					shape.dimensions[2] = hndf->getFloatValue();
				} else if(hndf->getVarName() == "rotation") {
					shape.rotation[0] = hndf->getFloatValue();
					shape.rotation[1] = hndf->getFloatValue();
					shape.rotation[2] = hndf->getFloatValue();
				}
			}

			break;
		}
		if(hndf->error()) {
			break;
		}
	}
}

}