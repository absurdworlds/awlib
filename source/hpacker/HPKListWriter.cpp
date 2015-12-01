/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "HPKListWriter.h"

namespace aw {
namespace itd {
HPKListWriter::HPKListWriter ()
{
}

HPKListWriter::~HPKListWriter ()
{
}

void HPKListWriter::addFile (std::string const& path, u64 id)
{
	u64 nameOffset = strings_.add(path);

	index_.push_back(ListEntry(nameOffset, id));
}

void HPKListWriter::write (std::ostream & target)
{
	// not needed, before I started writing this code, I planned to use
	// target.tellg() to determine offsets, but and came up with better 
	// idea after I started writing this class
	//u64 baseOffset = target.tellp();

	Header header;
	header.filesNum = index_.size();
	target.write((char *)&header.type,4);
	target.write((char *)&header.unused,4);
	target.write((char *)&header.filesNum,8);

	u64 nameBaseOffset = (index_.size()+1) * 16;

	for(auto & e : index_) {
		e.nameOffset += nameBaseOffset;
		target.write((char *)&e.nameOffset,8);
		target.write((char *)&e.fileId,8);
	}

	strings_.putStrings(target);
}

} //namespace itd
} //namespace aw
