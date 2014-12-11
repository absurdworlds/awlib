/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hpacker_
#define _hrengin_hpacker_
#include <string>
#include <vector>

#include <hrengin/common/types.h>
#include <hrengin/hitd/hitd.h>
#include <hrengin/io/CWriteFile.h>

#include "CItdFileTree.h"

namespace hrengin {
namespace itd {

class CItdPacker {
public:	
	CItdPacker (std::string const& archive_name, bool verbose = false);
	~CItdPacker ();

	/*!
	 * Add file to archive
	 */
	void addFile (std::string const& filename);
	/*!
	 * Add list of files
	 */
	void addList (std::vector<std::string> const& files);
	/*!
	 * Pack archive
	 */
	i32 pack ();

private:
	void buildFileList ();
	void addObject (std::string const& path);
	i32 addDir (std::string const& path);

	void writeHeader();

	void prepareFileIndex ();
	void updateFileIndex ();

	void buildFileTree ();

	void writeArchive();
	void packFile (size_t id, std::string const& path);

	std::vector<std::string> inputFiles_;
	std::vector<std::string> fileList_;
	std::vector<itd::FileEntry> index_;

	io::CWriteFile archive_;

	bool verbose_;
};
} // namespace itd
} // namespace hrengin
#endif//_hrengin_hpacker_
