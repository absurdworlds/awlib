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

SettingsManager* createSettingsManager()
{
	return new impl_::SettingsManager();
}

namespace impl_ {
SettingsManager::SettingsManager()
{
}

bool SettingsManager::getValue(std::string key, bool& val)
{
	return getValueImpl<bool>(key,val);
}

bool SettingsManager::getValue(std::string key, i32& val)
{
	return getValueImpl<i32>(key,val);
}

bool SettingsManager::getValue(std::string key, f64& val)
{
	return getValueImpl<f64>(key,val);
}

bool SettingsManager::getValue(std::string key, std::string& val)
{
	return getValueImpl<std::string>(key,val);
}

template<class T>
bool SettingsManager::getValueImpl(std::string key, T& val)
{
	auto found = indexMap_.find(key);

	if(found != indexMap_.end()) {
		return found->second.get<T>(val);
	}

	return false;
}

bool SettingsManager::setValue(std::string key, bool val)
{
	return setValueImpl<bool>(key,val);
}

bool SettingsManager::setValue(std::string key, i32 val)
{
	return setValueImpl<i32>(key,val);
}

bool SettingsManager::setValue(std::string key, f64 val)
{
	return setValueImpl<f64>(key,val);
}

bool SettingsManager::setValue(std::string key, std::string val)
{
	return setValueImpl<std::string>(key,val);
}

template<class T>
bool SettingsManager::setValueImpl(std::string key, T val)
{
	auto elem = indexMap_.insert(value_type(key,val));
	bool exists = !elem.second;

	if(exists) {
		hdf::Value& v = (elem.first)->second;
		return v.trySet<T>(val);
	}

	return true;
}
} // namespace impl_
} // namespace core
} // namespace hrengin
