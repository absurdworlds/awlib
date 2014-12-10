/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CArgParser_
#define _hrengin_CArgParser_
#include <string>
#include <vector>

#include <hrengin/common/types.h>
#include <hrengin/hitd/hitd.h>
#include <hrengin/io/CWriteFile.h>

namespace hrengin {
namespace itd {

class CItdPacker {
public:	
	CItdPacker (std::string const& archive_name);
	~CItdPacker ();

	/*!
	 * Add file to archive
	 */
	void add_file (std::string const& filename);
	/*!
	 * Pack archive
	 */
	i32 pack ();

private:
	i32 pack_archive ();
	i32 pack_object (std::string const& filename, io::CWriteFile& tmp);
	i32 pack_dir  (std::string const& path, io::CWriteFile& tmp);
	i32 pack_file (std::string const& path, io::CWriteFile& tmp);

	void write_header();
	void write_index();
	i32 write_archive();

	std::vector<std::string> input_files_;
	std::vector<std::string> files_to_pack_;

	std::vector<itd::FileEntry> index_;
	std::string name_;
	io::CWriteFile archive_;
	// Global offset for file data
	u64 globalOffset_;
};
} // namespace itd
} // namespace hrengin
#endif//_hrengin_CArgParser_
