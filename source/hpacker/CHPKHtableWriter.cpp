/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <random>

#include "CHPKHtableWriter.h"

namespace hrengin {
namespace itd {
CHPKHtableWriter ()
	: stringsTally_(0)
{
	std::random_device rd;
	std::mt19937 mt_eng(rd());

	std::uniform_int_distribution udist;

	seed_.as64[0] = udist(mt_eng);
	seed_.as64[1] = udist(mt_eng);
}

CHPKHtableWriter::~CHPKHtableWriter ()
{
}

void CHPKHtableWriter::write (std::ostream& target);
{
	Header header;
	header.filesNum = index_.size();
	header.seed = seed_;

	u64 nameBaseOffset = (header.filesNum + 1) * 32;
	while(index_.size() > 0) {
		u64 num = index.size();

		u128 hash;
		std::string& path = strings_[num];
		MurmurHash3_x64_128(path.data(), path.size(), seed_, &hash);

		u64 i = hash.as64[0] % header.filesNum;

		index_.back().nameOffset += nameBaseOffset;
		htable_[i].add(index_.back());

		index_.pop_back();
	}

	target_.write((char *)&header.type,4);
	target_.write((char *)&header.unused,4);
	target_.write((char *)&header.filesNum,8);
	target_.write((char *)&header.seed,16);

	u64 listTally = 0;
	for(auto & h : htable_) {
		h.entriesOffset = (header.filesNum + listTally)*16;
		h.fileListSize = h.list.size()
		listTally += fileListSize;

		if(h.fileListSize > 1) {
			// Warning: hash collision
		}

		target_.write((char *)&h.entriesOffset,8);
		target_.write((char *)&h.fileListSize,8);
	}

	for(auto & h : htable_) {
		for(auto & e : h.list) {
			target_.write(&e.nameOffset,8);
			target_.write(&e.fileId,8);
		}
	}

	for(auto str : strings_) {
		// truncate size
		u16 size = str.size() + 1;
		target_.write(&size,2);
		target_.write(str.c_str(), str.size() + 1);
	}
}

} //namespace itd
} //namespace hrengin

