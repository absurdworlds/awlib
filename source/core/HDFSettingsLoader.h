/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_HDFSettingsLoader_
#define _hrengin_HDFSettingsLoader_
#include <hrengin/resources/default_settings.h>
#include <hrengin/io/ReadFile.h>
#include <hrengin/io/BufferedStream.h>
#include <hrengin/hdf/HDFParser.h>

#include <hrengin/core/SettingsLoader.h>

namespace hrengin {
namespace core {

class HDFSettingsLoader : public SettingsLoader {
public:
	HDFSettingsLoader (io::ReadFile & file, SettingsManager & manager);
	virtual ~HDFSettingsLoader ()
	{
	}

	virtual void loadSettings ();

protected:
	void parseSettings (hdf::HDFParser * hdf);

private:
	//std::string hdfFile_;
	io::ReadFile & file_;
	SettingsManager & manager_;
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_HDFSettingsLoader_
