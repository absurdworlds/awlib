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
// ITD : Intelligently Trampled Data
// source:
// (09:23:04 AM) Spectre: gcfscape185(открыча гцф впк итд).zip
namespace itd {
#ifdef HR_MODULE_ITD
	#define HR_ITD_EXP HR_EXPORT
#else
	#define HR_ITD_EXP HR_IMPORT
#endif

/*!
 * Main header contains format identifier and some additional information,
 * such as timestamp and number of files.
 */
struct MainHeader {
	MainHeader ()
		: fileId{'h','i','t','d'}, padding{0}
	{
	}

	//! File type indetifier, should be 'hitd'
	u8 const fileId[4];
	//! hrengin package format version
	u32 version;
	//! Time packaged;
	u64 ptime;
	//! Number of file entries
	u64 files_num;
	//! Flags
	u16 flags;
	//! Padding to 32 bytes
	u8 padding[6];
};

//! Package flags (reserved)
enum Flags : u16 {

};

/*!
 * Secondary header, used to define format extensions.
 */
struct SecondHeader {
	SecondHeader ()
		: padding{0}
	{
	}
	//! Secondary identifier, application-specific
	u8 id[4];
	//! Secondary format version
	u32 version;
	u8 padding[24];
};

/*!
 * Second header for standard archive
 */
struct StandardHeader {
	StandardHeader ()
		: id{'h','p','k','a'}, padding{0}
	{
	}

	u8 id[4];
	u32 version;
	u32 flags;
	u8 padding[20];
};

enum StandardFlags : u32 {
	STD_HasFileTree 	= 1 << 0,
	STD_HasHashTable	= 1 << 1,
	STD_HasFileMeta		= 1 << 2,
};

/*!
 * Header of ITD, provides file identifier and some additional
 * information adbout archive
 */
struct Header {
	struct MainHeader main;
	struct SecondHeader second;
};

//! File flags
enum FileFlags : u16 {
	None,
	//! Specifies whether file can be executed.
	Exec = 1,
};

//! Represents a file entry
struct FileEntry {
	//! Position of first element from beginning of the package
	u64 offset;
	//! Size of file in bytes
	u64 size;
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
