/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_ItdPacker_
#define _aw_ItdPacker_
#include <string>
#include <vector>
#include <fstream>

#include <aw/common/types.h>
#include <aw/itd/itd.h>
#include <aw/itd/HPKIndexWriter.h>

namespace aw {
namespace itd {

class ItdPacker {
public:	
	ItdPacker (std::string const& archive_name, bool verbose = false);
	~ItdPacker ();

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
	i32 addDir (std::string const& path);

	void writeHeader();

	void buildIndex ();

	void writeArchive();
	void packFile (size_t id, std::string const& path);

	std::vector<std::string> fileList_;
	std::vector<itd::FileEntry> index_;

	std::ofstream archive_;

	bool verbose_;

};
} // namespace itd
} // namespace aw
#endif//_aw_ItdPacker_
