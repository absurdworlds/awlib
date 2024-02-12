/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_itd_hpk_h
#define aw_itd_hpk_h
#include <string>
#include <aw/types/types.h>

namespace aw {
namespace itd {
namespace v5 {
struct package_header {
	//! File type indetifier, should be '.itd'
	u8 id[4] = {'.','i','t','d'};
	//! format version
	u8 version = 5;
	//! flags (unused)
	u16 flags = 0;
	//! Number of file entries
	u64 file_count = 0;
	//! Secondary identifier, application-specific
	u8 id2[4] = {};
	//! Reserved
	u8 padding[48] = {};
};
} // namespace v0

enum hpk_flags : u16 {
	has_file_tree = 1 << 0,
	has_metadata  = 1 << 1,
};

/*!
 * Second header for HPK archive
 */
struct hpk_header {
	hpk_header ()
		: id{'h','p','k','a'}, padding{0}
	{
	}
	u8 id[4];
	//! HPK format version
	u16 version;
	//! HPK 
	hpk_flags flags;
	//! Time packaged;
	i64 ptime;
	u8 padding[32];
};


} // namespace itd
} // namespace aw
#endif//aw_itd_hpk_h
