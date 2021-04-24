/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_ItdPacker_h
#define aw_internal_ItdPacker_h
#include <string>
#include <vector>
#include <fstream>

#include <aw/types/types.h>
#include <aw/itd/itd.h>
#include <aw/itd/HPKIndexWriter.h>

namespace aw {
namespace itd {
struct ItdPacker {
	ItdPacker(std::ostream& archive, bool verbose = false);
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

	std::ostream& archive_;

	bool verbose_;

};
} // namespace itd
} // namespace aw
#endif//aw_internal_ItdPacker_h
