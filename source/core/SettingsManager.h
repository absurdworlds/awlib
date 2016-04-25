/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_SettingsManager_impl_
#define _aw_SettingsManager_impl_
#include <map>

#include <aw/hdf/Value.h>

#include <aw/core/SettingsManager.h>

namespace aw {
namespace core {
namespace impl_ {
// Implementation of core::SettingsManager interface
class SettingsManager : public core::SettingsManager {
public:
	SettingsManager();
	virtual ~SettingsManager()
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
	template<class T>
	bool setValueImpl(std::string key, T val);

	template<class T>
	bool getValueImpl(std::string key, T& val);

	std::map<std::string, hdf::Value> indexMap_;

	typedef std::map<std::string, hdf::Value>::value_type value_type;
};

} // namespace impl_
} // namespace core
} // namespace aw
#endif//_aw_SettingsManager_impl_
