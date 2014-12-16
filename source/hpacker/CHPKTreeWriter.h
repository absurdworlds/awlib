/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CHPKTreeWriter_
#define _hrengin_CHPKTreeWriter_
#include <vector>

#include <hrengin/itd/IHPKIndexWriter.h>

#include "CStringBank.h"

namespace hrengin {
namespace itd {

struct ListEntry {
	ListEntry (u64 name, u64 id)
		: nameOffset(name), id(id)
	{
	}
	u64 nameOffset;
	u64 id;
};

struct TreeNode {
	void add (std::vector<std::string> path, std::string name, u64 id,
		CStringBank & strings);
	void calcOffsets (u64 & baseOffset);
	void writeOut (std::ostream & target, u64 baseOffset);

	u64 nameOffset;
	u64 filesPtr;
	u32 filesNum;
	u64 subtreePtr;
	u32 subtreeNum;

	std::string name;
	std::vector<TreeNode> leaves;
	std::vector<ListEntry> files;
};

/*!
 * Interface for building HPKA tree index
 */
class CHPKTreeWriter : IHPKIndexWriter {
public:
	CHPKTreeWriter ();

	virtual ~CHPKTreeWriter ();

	virtual void addFile (std::string const& path, u64 id);
	virtual void write (std::ostream& target);
private:
	void addFile (std::vector<std::string> path,
			std::string name, u64 id);
protected:

	struct Header {
		Header ()
			: type{'t','r','e','e'}, unused{0}
		{
		}

		u8 type[4];
		u8 unused[4];
	};

	TreeNode root_;
	std::vector<ListEntry> files_;
	std::vector<TreeNode> dirs_;

	CStringBank strings_;
};

} //namespace itd
} //namespace hrengin
#endif//_hrengin_CHPKTreeWriter_
