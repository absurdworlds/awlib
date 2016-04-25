/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <random>

#include "HPKHtableWriter.h"

namespace aw {
namespace itd {
HPKHtableWriter::HPKHtableWriter ()
	: HPKListWriter()
{
	std::random_device rd;
	std::mt19937_64 mt_eng(rd());

	std::uniform_int_distribution<u64> udist;

	seed_.as64[0] = udist(mt_eng);
	seed_.as64[1] = udist(mt_eng);
}

HPKHtableWriter::~HPKHtableWriter ()
{
}

void HPKHtableWriter::write (std::ostream& target)
{
	Header header;
	header.filesNum = index_.size();
	header.seed = seed_;

	u64 nameBaseOffset = (header.filesNum + 1) * 32;
	while(index_.size() > 0) {
		u64 num = index_.size();

		u128 hash;
		std::string const & path = strings_[num];
		MurmurHash3_x64_128(path.data(), path.size(), seed_, &hash);

		u64 i = hash.as64[0] % header.filesNum;

		index_.back().nameOffset += nameBaseOffset;
		htable_[i].add(index_.back());

		index_.pop_back();
	}

	target.write((char *)&header.type,4);
	target.write((char *)&header.unused,4);
	target.write((char *)&header.filesNum,8);
	target.write((char *)&header.seed,16);

	u64 listTally = 0;
	for(auto & h : htable_) {
		h.entriesOffset = (header.filesNum + listTally)*16;
		h.fileListSize = h.list.size();
		listTally += h.fileListSize;

		if(h.fileListSize > 1) {
			// Warning: hash collision
		}

		target.write((char *)&h.entriesOffset,8);
		target.write((char *)&h.fileListSize,8);
	}

	for(auto & h : htable_) {
		for(auto & e : h.list) {
			target.write((char *)&e.nameOffset,8);
			target.write((char *)&e.fileId,8);
		}
	}

	strings_.putStrings(target);
}

} //namespace itd
} //namespace aw
