/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_HDFSettingsLoader_
#define _aw_HDFSettingsLoader_
#include <aw/io/ReadFile.h>
#include <aw/io/BufferedStream.h>
#include <aw/hdf/Parser.h>

#include <aw/core/SettingsLoader.h>

namespace aw {
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
} // namespace aw
#endif//_aw_HDFSettingsLoader_
