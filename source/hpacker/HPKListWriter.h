/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_HPKListWriter_h
#define aw_HPKListWriter_h
#include <vector>

#include <aw/itd/HPKIndexWriter.h>

#include "StringBank.h"

namespace aw {
namespace itd {
/*!
 * Interface for building HPKA list index
 */
class HPKListWriter : public HPKIndexWriter {
public:
	HPKListWriter ();

	virtual ~HPKListWriter ();

	virtual void addFile (std::string const & path, u64 id);
	virtual void write (std::ostream & target);
private:
protected:
	struct ListEntry {
		ListEntry (u64 name, u64 id)
			: nameOffset(name), fileId(id)
		{
		}

		u64 nameOffset;
		u64 fileId;
	};

	struct Header {
		Header ()
			: type{'l','i','s','t'}, unused{0}
		{
		}

		u8 type[4];
		u8 unused[4];
		u64 filesNum;
	};

	StringBank strings_;
	std::vector<ListEntry> index_;
};

} //namespace itd
} //namespace aw
#endif//_aw_HPKListWriter_
