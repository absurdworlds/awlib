/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IHPKTreeWriter_
#define _hrengin_IHPKTreeWriter_
#include <vector>

#include <hrengin/itd/IHPKIndexWriter.h>

namespace hrengin {
namespace itd {

struct FileEntry {
	u64 nameOffset;
	u64 id;
};

struct TreeNode {
	void calcOffsets (u64 & baseOffset, CStringBank & strings);

	u64 nameOffset;
	u64 filesPtr;
	u32 filesNum;
	u64 subtreePtr;
	u32 subtreeNum;

	std::string name;
	std::vector<TreeNode> leaves;
	std::vector<FileEntry> files;
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
		u8 type[4];
		u8 unused[4];
	};



	TreeNode root_;
	std::vector<FileEntry> files_;
	std::vector<TreeNode> dirs_;

	std::vector<std::string> strings_;
private:
	u64 stringsTally_;
};

} //namespace itd
} //namespace hrengin
#endif//_hrengin_IHPKTreeWriter_
