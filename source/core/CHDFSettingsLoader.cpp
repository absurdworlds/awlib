/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <fstream>

#include <hrengin/io/filesystem.h>

#include "CHDFSettingsLoader.h"

i32 CHDFSettingsLoader::openFile(std::string const & path)
{
	FileInfo finfo = fileStat(path);

	if(finfo.type != io::FileType::File) {
		return -1;
	}

	std::ifstream in;
	in.open(path, std::ios::binary);
	size_t size = finfo.size;

	hdfFile_.reserve(size);
	
	in.read(&hdfFile_[0], size);
}

void CHDFSettingsLoader::loadSettings()
{
	hdf::IHDFParser* hdf;


	if(file) {
		hdf = hdf::createHDFParser(file);
	} else {
		std::string def(default_settings);
		std::istringstream sstream(def);

		hdf = hdf::createHDFParser(sstream);
	}

	parseSettings(hdf);

	delete hdf;
}

void CHDFSettingsLoader::parseSettings(hdf::IHDFParser* hdf)
{
	std::string prevNode;
	std::string curNode;
	std::string curObj;
	while(hdf->read()) {
		switch(hdf->getObjectType()) {
		case hdf::HDF_OBJ_NODE:
			if(curNode == "") {
				hdf->getObjectName(curNode);
			} else if(curNode == "settings") {
				prevNode = curNode;
				hdf->getObjectName(curNode);
			} else {
				hdf->skipNode();
			}
			break;
		case hdf::HDF_OBJ_NODE_END:
			if (curNode != "settings") {
				curNode = prevNode;
				prevNode = "";
			} else {
				curNode = "";
			}
			break;
		case hdf::HDF_OBJ_VAL:
			hdf->getObjectName(curObj);
			if(curNode == "graphics") {
				if(curObj == "resolutionX") {
					i32 temp;
					hdf->readInt(temp);
					
					setValue(curNode + "." + curObj, temp);
				} else if (curObj == "resolutionY") {
					i32 temp;
					hdf->readInt(temp);
					
					setValue(curNode + "." + curObj, temp);
				} else if (curObj == "fullscreen") {
					bool temp;
					hdf->readBool(temp);
					
					setValue(curNode + "." + curObj, temp);
				}
			}
			break;
		default:
			return;
		}
	}
}


