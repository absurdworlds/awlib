/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IHPKHtableWriter_
#define _hrengin_IHPKHtableWriter_
#include <vector>

#include <hrengin/core/hash.h>
#include "CHPKListWriter.h"

namespace hrengin {
namespace itd {
/*!
 * Interface for building HPKA hash table index
 */
class CHPKHtableWriter : public CHPKListWriter {
public:
	CHPKHtableWriter ();

	virtual ~CHPKHtableWriter ();

	virtual void addFile (std::string const& path, u64 id);
	virtual void write (std::ostream& target);
private:
	typedef CHPKListWriter::ListEntry ListEntry;
	struct HtableEntry {
		HtableEntry ()
			: entriesOffset(-1), fileListSize(0)
		{
		}

		void add (ListEntry const & entry)
		{
			list.push_back(entry);
		}

		bool empty ()
		{
			return list.empty();
		}
		
		u64 entriesOffset;
		u64 fileListSize;

		std::vector<ListEntry> list;
	};

	struct Header : public CHPKListWriter::Header {
		Header ()
			: type{'h','t','b','l'}, unused{0}
		{
		}

		u128 seed;
	};

	std::vector<HtableEntry> htable_;
	u128 seed_;
};

} //namespace itd
} //namespace hrengin
#endif//_hrengin_IHPKHtableWriter_
