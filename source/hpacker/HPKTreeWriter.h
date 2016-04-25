/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_HPKTreeWriter_
#define _aw_HPKTreeWriter_
#include <vector>

#include <aw/itd/HPKIndexWriter.h>

#include "StringBank.h"

namespace aw {
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
		StringBank & strings);
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
class HPKTreeWriter : public HPKIndexWriter {
public:
	HPKTreeWriter ();

	virtual ~HPKTreeWriter ();

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

	StringBank strings_;
};

} //namespace itd
} //namespace aw
#endif//_aw_HPKTreeWriter_
