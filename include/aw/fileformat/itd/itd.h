/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_itd_itd_h
#define aw_itd_itd_h
#include <string>
#include <aw/types/types.h>

namespace aw {
//! itd: a simple archive format
//
// \note the name doesn't mean anything, just chose something that won't
// conflict with other filenames
namespace itd {
inline namespace v6 {
//! Package flags (reserved)
enum class package_flags : u8 {
	no_flags = 0,

};

/*!
 * Main header contains format identifier and some additional information,
 * such as timestamp and number of files.
 */
struct package_header {
	//! File type indetifier, should be '.itd'
	uint8_t        id[4]        = {'.','i','t','d'};
	//! format version
	uint8_t        version      = 6;
	//! size of the header in multiples of 32 bytes
	uint8_t        header_size  = 1;
	//! number of rezerved file entries
	uint8_t        reserved_entries = 0;
	//! reserved
	package_flags  flags = package_flags::no_flags;
	//! number of file entries
	uint64_t       file_count   = 0;
};


struct second_header {
};

//! File flags
enum file_flags : u16 {
	none,
	//! Specifies whether file can be executed.
	exec = 1,
};

//! Represents a file entry
struct file_entry {
	//! Position of first element from beginning of the package
	u64 offset = -1;
	//! Size of file in bytes
	u64 size   = 0;
};

} // namespace v6
} // namespace itd
} // namespace aw
#endif//aw_itd_itd_h
