/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CHDFSettingsLoader_
#define _hrengin_CHDFSettingsLoader_
#include <hrengin/io/CReadFile.h>
#include <hrengin/hdf/hdf_value.h>

#include <hrengin/core/ISettingsLoader.h>

namespace hrengin {
namespace core {

class CHDFSettingsLoader : public ISettingsLoader {
public:
	CHDFSettingsLoader (io::CReadFile & file);
	virtual ~CHDFSettingsLoader ()
	{
	}

	virtual void loadSettings (ISettingsManager & manager);

protected:
	void parseSettings (hdf::IHDFParser* hdf);

private:
	//std::string hdfFile_;
	io::CReadFile & file_;
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_CHDFSettingsLoader_
