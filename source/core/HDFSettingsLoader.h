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
#include <awengine/io/ReadFile.h>
#include <awengine/io/BufferedStream.h>
#include <awengine/hdf/Parser.h>

#include <awengine/core/SettingsLoader.h>

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
	void parseSettings (hdf::Parser * hdf);

private:
	//std::string hdfFile_;
	io::ReadFile & file_;
	SettingsManager & manager_;
};

} // namespace core
} // namespace awrts
#endif//_awrts_HDFSettingsLoader_
