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

enum Action {
	Create,
	Unpack,
	List
};

class CItdPacker {
public:	
	CItdPacker (std::string name);
	~CItdPacker ();

	i32 pack (std::string path, bool recursive);

	i32 packDir (std::string path, bool recursive, io::CWriteFile& tmp);
	i32 addFile (std::string path, io::Dirent file, io::CWriteFile& tmp);

	i32 writeIndex();
	i32 writeArchive();

private:
	std::vector<itd::FileEntry> index_;
	std::string name_;
	io::CWriteFile archive_;
	// Global offset for file data
	u64 globalOffset_;
};
} // namespace itd
} // namespace hrengin
#endif//_hrengin_CArgParser_
