/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IHPKListWriter_
#define _hrengin_IHPKListWriter_
#include <vector>

#include <hrengin/itd/IHPKIndexWriter.h>

#include "CStringBank.h"

namespace hrengin {
namespace itd {
/*!
 * Interface for building HPKA list index
 */
class CHPKListWriter : public IHPKIndexWriter {
public:
	CHPKListWriter ();

	virtual ~CHPKListWriter ();

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

	CStringBank strings_;
	std::vector<ListEntry> index_;
};

} //namespace itd
} //namespace hrengin
#endif//_hrengin_IHPKListWriter_
