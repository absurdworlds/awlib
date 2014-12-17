/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CSettingsManager_
#define _hrengin_CSettingsManager_
#include <map>

#include <hrengin/core/ISettingsManager.h>

#include <hrengin/hdf/hdf_value.h>

namespace hrengin {
namespace core {

class CSettingsManager : public ISettingsManager {
public:
	CSettingsManager();
	virtual ~CSettingsManager()
	{
	}

	//virtual void registerSetting(std::string key, hdf::Type type);

	virtual bool getValue(std::string key, std::string& val);
	virtual bool getValue(std::string key, f64& val);
	virtual bool getValue(std::string key, i32& val);
	virtual bool getValue(std::string key, bool& val);

	virtual bool setValue(std::string key, std::string val);
	virtual bool setValue(std::string key, f64 val);
	virtual bool setValue(std::string key, i32 val);
	virtual bool setValue(std::string key, bool val);
private:
	void parseSettings(hdf::IHDFParser* hdf);
	
	template<class T>
	bool setValueImpl(std::string key, T val);
	
	template<class T>
	bool getValueImpl(std::string key, T& val);
	
	std::map<std::string, hdf::Value> indexMap_;
	
	typedef std::map<std::string, hdf::Value>::value_type value_type;
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_CSettingsManager_
