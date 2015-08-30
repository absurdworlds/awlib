/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_HDFSettingsLoader_
#define _awrts_HDFSettingsLoader_
#include <awrts/resources/default_settings.h>
#include <awrts/io/ReadFile.h>
#include <awrts/io/BufferedStream.h>
#include <awrts/hdf/HDFParser.h>

#include <awrts/core/SettingsLoader.h>

namespace awrts {
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
} // namespace awrts
#endif//_awrts_HDFSettingsLoader_
