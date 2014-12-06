/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_itd_
#define _hrengin_itd_

#include <string>
#include <hrengin/common/types.h>

namespace hrengin {
// source:
// (09:23:04 AM) Spectre: gcfscape185(открыча гцф впк итд).zip
//! ITD : Intelligently Trampled Data
namespace itd {
#ifdef HR_MODULE_ITD
	#define HR_ITD_EXP HR_EXPORT
#else
	#define HR_ITD_EXP HR_IMPORT
#endif

//! Package flags (reserved)
enum Flags : u16 {

};

//! Header of ITD
struct Header {
	//! File type indetifier
	u32 const fileId; // 'hitd'
	//! hrengin package format version
	u32 version;
	//! Time packaged;
	u64 ptime;
	//! Flags
	Flags flags;
};

//! File flags
enum FileFlags : u16 {
	//! Specifies whether file can be executed.
	Exec = 1,
};

//! Represents a file entry
struct FileEntry {
	//! Position of first element from beginning of the package
	u64 offset;
	//! Size of file in bytes
	u64 size;
	//! File modification time
	u64 mtime;
	//! Flags
	FileFlags flags;
	//! 
	u16 reserved[3];
};

#if 0
struct PackageIndexEntry {
	u8* packageName;
	u8* physicalPath;
	FileTypes fileTypes;
};
#endif

} // namespace itd
} // namespace hrengin
#endif//_hrengin_hitd_
