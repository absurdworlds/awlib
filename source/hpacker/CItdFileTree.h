/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CItdFileTree_
#define _hrengin_CItdFileTree_
#include <memory>
#include <algorithm>
#include <string>
#include <vector>

#include <hrengin/common/types.h>
#include <hrengin/common/stringutils.h>
#include <hrengin/io/CWriteFile.h>

namespace hrengin {
namespace itd {

struct FileTree;

struct TreeEntry {
	TreeEntry (std::string path, u64 id)
		: name(path), id(id)
	{
	}
	std::string name;
	u64 id;
};

struct TreeLeaf {
	TreeLeaf (std::string name, FileTree* tree)
		: name(name), tree(tree), position(0)
	{
	}
	std::string name;
	std::unique_ptr<FileTree> tree;		
	u64 position;
};

struct FileTree {
	std::vector<TreeLeaf> leaves_;
	std::vector<TreeEntry> files_;

	void addFile (std::string const& path, u64 id);
	void addFile (std::vector<std::string> path, u64 id);

	void write (io::CWriteFile& target);
private:
	void findAndAdd (std::string const& name,
		std::vector<std::string> path, u64 id);
	u64 writeTree (io::CWriteFile& target);
	void writeDirList (io::CWriteFile& target);
};

} // namespace itd
} // namespace hrengin
#endif//_hrengin_CItdFileTree_
