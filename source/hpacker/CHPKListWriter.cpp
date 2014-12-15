/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "CHPKListWriter.h"

namespace hrengin {
namespace itd {
CHPKListWriter ()
	: stringsTally_(0)
{
}

CHPKListWriter::~CHPKListWriter ()
{
}

void CHPKListWriter::addFile (std::string const& path, u64 id);
{
	u64 nameOffset = stringsTally_;
	stringsTally_ += 3 + path.size();

	strings_.push_back(path);
	index_.push_back(ListEntry(nameOffset, id));
}

void CHPKListWriter::write (std::ostream& target);
{
	// not needed, before I started writing this code, I planned to use
	// target.tellg() to determine offsets, but and came up with better 
	// idea after I started writing this class
	//u64 baseOffset = target.tellp();

	Header header;
	header.filesNum = index_.size();
	target_.write((char *)&header.type,4);
	target_.write((char *)&header.unused,4);
	target_.write((char *)&header.filesNum,8);
	
	u64 nameBaseOffset = (index_.size()+1) * 16;

	for(size_t i = 0; i < index_.size(); ++i) {
		index_[i].nameOffset += nameBaseOffset;
		target_.write(&index_[i].nameOffset,8);
		target_.write(&index_[i].fileId,8);
	}

	putStrings();
}

void CHPKListWriter::putStrings()
{
	for(auto str : strings_) {
		// truncate size
		u16 size = str.size() + 1;
		target_.write(&size,2);
		target_.write(str.c_str(), str.size() + 1);
	}
}

} //namespace itd
} //namespace hrengin
