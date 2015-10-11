/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <fstream>

#include <awengine/io/filesystem.h>

#include "HDFSettingsLoader.h"

namespace awrts {
namespace core {

#if 0
i32 HDFSettingsLoader::openFile(std::string const & path)
{
	FileInfo finfo = fileStat(path);

	if(finfo.type != io::FileType::File) {
		return -1;
	}

	size_t size = finfo.size;

	hdfFile_.reserve(size);

	in.read(&hdfFile_[0], size);
}
#endif

HDFSettingsLoader::HDFSettingsLoader (io::ReadFile& file,
		SettingsManager& settings)
	: file_(file), manager_(settings)
{
}

std::string fallback_settings = "[]";

void HDFSettingsLoader::loadSettings ()
{
	io::CharacterStream* stream;
	hdf::Parser* hdf;

	stream = file_.isOpen() 
		? io::createBufferedStream(file_)
		: io::createCharacterStream(fallback_settings.c_str());

	hdf = hdf::createParser(stream);

	parseSettings(hdf);

	delete hdf;
	delete stream;
}

void HDFSettingsLoader::parseSettings (hdf::Parser* hdf)
{
	std::string prevNode;
	std::string curNode;
	std::string curObj;
	while(hdf->read()) {
		// FIXME: write generic parser
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

					manager_.setValue(curNode + "." + curObj, temp);
				} else if (curObj == "resolutionY") {
					i32 temp;
					hdf->readInt(temp);

					manager_.setValue(curNode + "." + curObj, temp);
				} else if (curObj == "fullscreen") {
					bool temp;
					hdf->readBool(temp);

					manager_.setValue(curNode + "." + curObj, temp);
				}
			}
			break;
		default:
			return;
		}
	}
}

} // namespace core
} // namespace awrts
