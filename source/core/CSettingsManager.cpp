/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <hrengin/resources/default_settings.h>
#include <hrengin/common/singleton.h>
#include <hrengin/core/IHDFParser.h>
#include <hrengin/io/IReadFile.h>
#include <hrengin/io/ICharacterStream.h>
#include <hrengin/io/IBufferedStream.h>

#include "CSettingsManager.h"

namespace hrengin {
namespace core {

ISettingsManager* createSettingsManager()
{
	return new CSettingsManager();
}

ISettingsManager& getSettingsManager()
{
	return makeSingleton<CSettingsManager>();
}

CSettingsManager::CSettingsManager()
{
//	loadSettings();
}

void CSettingsManager::loadSettings()
{
	io::IReadFile* file = io::openReadFile("../data/settings.hdf");
	io::ICharacterStream* stream;
	hdf::IHDFParser* hdf;

	stream = file ? io::createBufferedStream(file)
		: io::createCharacterStream(default_settings);

	hdf = hdf::createHDFParser(stream);
	parseSettings(hdf);

	delete hdf;
	delete stream;
	delete file;
}

void CSettingsManager::parseSettings(hdf::IHDFParser* hdf)
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


bool CSettingsManager::getValue(std::string key, bool& val)
{
	return getValueImpl<bool>(key,val);
}

bool CSettingsManager::getValue(std::string key, i32& val)
{
	return getValueImpl<i32>(key,val);
}

bool CSettingsManager::getValue(std::string key, f64& val)
{
	return getValueImpl<f64>(key,val);
}

bool CSettingsManager::getValue(std::string key, std::string& val)
{
	return getValueImpl<std::string>(key,val);
}

template<class T>
bool CSettingsManager::getValueImpl(std::string key, T& val)
{
	auto found = indexMap_.find(key);

	if(found != indexMap_.end()) {
		return found->second.get<T>(val);
	}

	return false;
}

bool CSettingsManager::setValue(std::string key, bool val)
{
	return setValueImpl<bool>(key,val);
}

bool CSettingsManager::setValue(std::string key, i32 val)
{
	return setValueImpl<i32>(key,val);
}

bool CSettingsManager::setValue(std::string key, f64 val)
{
	return setValueImpl<f64>(key,val);
}

bool CSettingsManager::setValue(std::string key, std::string val)
{
	return setValueImpl<std::string>(key,val);
}

template<class T>
bool CSettingsManager::setValueImpl(std::string key, T val)
{
	auto elem = indexMap_.insert(value_type(key,val));
	bool exists = !elem.second;

	if(exists) {
		hdf::Value& v = (elem.first)->second;
		return v.trySet<T>(val);
	}

	return true;
}

} // namespace core
} // namespace hrengin
