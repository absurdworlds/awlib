/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/io/ReadFile.h>
#include <hrengin/io/CharacterStream.h>
#include <hrengin/io/BufferedStream.h>

#include "SettingsManager.h"

namespace hrengin {
namespace core {

SettingsManager_* createSettingsManager()
{
	return new SettingsManager_();
}

SettingsManager_::SettingsManager_()
{
}

bool SettingsManager_::getValue(std::string key, bool& val)
{
	return getValue_<bool>(key,val);
}

bool SettingsManager_::getValue(std::string key, i32& val)
{
	return getValue_<i32>(key,val);
}

bool SettingsManager_::getValue(std::string key, f64& val)
{
	return getValue_<f64>(key,val);
}

bool SettingsManager_::getValue(std::string key, std::string& val)
{
	return getValue_<std::string>(key,val);
}

template<class T>
bool SettingsManager_::getValueImpl(std::string key, T& val)
{
	auto found = indexMap_.find(key);

	if(found != indexMap_.end()) {
		return found->second.get<T>(val);
	}

	return false;
}

bool SettingsManager_::setValue(std::string key, bool val)
{
	return setValue_<bool>(key,val);
}

bool SettingsManager_::setValue(std::string key, i32 val)
{
	return setValue_<i32>(key,val);
}

bool SettingsManager_::setValue(std::string key, f64 val)
{
	return setValue_<f64>(key,val);
}

bool SettingsManager_::setValue(std::string key, std::string val)
{
	return setValue_<std::string>(key,val);
}

template<class T>
bool SettingsManager_::setValueImpl(std::string key, T val)
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
