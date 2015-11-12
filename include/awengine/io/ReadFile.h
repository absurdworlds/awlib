/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_ReadFile_
#define _awrts_ReadFile_
#include <awengine/io/File.h>

namespace awrts {
namespace io {
/*!
 * Provides interface for reading files
 */
class AW_IO_EXP ReadFile : private File {
public:
	ReadFile (std::string const& path)
		: File(path, File::Read)
	{
	}

	virtual ~ReadFile() = default;

	using File::isOpen;
	using File::close;
	using File::read;
	using File::seek;
	using File::tell;
	using File::getSize;
	using File::getPath;
};

} // namespace io
} // namespace awrts
#endif//_awrts_ReadFile_
