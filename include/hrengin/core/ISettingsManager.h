/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISettingsManager_
#define _hrengin_ISettingsManager_

#include <string>

#include <hrengin/core/api.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace core {

//! Interface is used to load, access and store different settings
class ISettingsManager {
public:
	//! Virtual destructor
	virtual ~ISettingsManager() {};
	
	//! Load and parse settings from file 'settings.hdf'
	virtual void loadSettings() = 0;

	//virtual void registerSetting(std::string key, hdf::Type type) = 0;

	virtual bool getValue(std::string key, std::string& val) = 0;
	virtual bool getValue(std::string key, f64& val) = 0;
	virtual bool getValue(std::string key, i32& val) = 0;
	virtual bool getValue(std::string key, bool& val) = 0;

	virtual bool setValue(std::string key, std::string val) = 0;
	virtual bool setValue(std::string key, f64 val) = 0;
	virtual bool setValue(std::string key, i32 val) = 0;
	virtual bool setValue(std::string key, bool val) = 0;
};

HR_CORE_API ISettingsManager& getSettingsManager();
//HR_CORE_API ISettingsManager* createSettingsManager();

} // namespace core
} // namespace hrengin


#endif//_hrengin_ISettingsManager_
