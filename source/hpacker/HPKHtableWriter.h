/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_HPKHtableWriter_h
#define aw_internal_HPKHtableWriter_h
#include <vector>

#include <aw/utility/hash.h>

#include "HPKListWriter.h"

namespace aw {
namespace itd {
/*!
 * Interface for building HPKA hash table index
 */
class HPKHtableWriter : public HPKListWriter {
public:
	HPKHtableWriter();

	virtual ~HPKHtableWriter();

	virtual void write(std::ostream& target);
private:
	typedef HPKListWriter::ListEntry ListEntry;
	struct HtableEntry {
		HtableEntry()
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

	struct Header {
		Header ()
			: type{'h','t','b','l'}, unused{0}
		{
		}

		u8 type[4];
		u8 unused[4];
		u64 filesNum;
		u128 seed;
	};

	std::vector<HtableEntry> htable_;
	u128 seed_;
};

} //namespace itd
} //namespace aw
#endif//aw_internal_HPKHtableWriter_h
