/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CSettingsManager_
#define _hrengin_CSettingsManager_

#include <map>
#include <vector>

#include <hrengin/core/hdf_value.h>
#include <hrengin/core/ISettingsManager.h>

namespace hrengin {
namespace core {

#if 0
/* 
   Struct is used to determine in which vector the Setting is stored,
   additionally to storing it's index in vector;
 */
union SettingId {
	struct {
		hdf::Type type;
		u32 id;
	};
	u64 index;
};
#endif

class CSettingsManager : public ISettingsManager {
public:
	CSettingsManager();
	virtual ~CSettingsManager() {};

	virtual void loadSettings();

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

#if 0	// I left this here, so a different approach
	// which I tested first will be reflected in commit history

	template<class T, std::vector<T>& container>
	void setValueImpl(std::string key, T val);
	
	template<class T, std::vector<T>& container>
	void getValueImpl(std::string key, T& val);

	std::map<std::string, SettingId> indexMap_;
	struct Settings {
		std::vector<i32> i;
		std::vector<f64> f;
		std::vector<std::string> s;
		std::vector<bool> b;
	} settings_;
#endif
};

} // namespace core
} // namespace hrengin

#endif//_hrengin_CSettingsManager_
