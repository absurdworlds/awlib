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
	u64 id
};

struct TreeLeaf {
	TreeLeaf (std::string name, FileTree* tree)
		: name(name), tree(tree)
	{
	}
	std::string name;
	std::unique_ptr<FileTree> tree;		
	u64 position;
};

struct FileTree {
	std::vector<TreeLeaf> leaves_;
	std::vector<TreeEntry> files_;

	void addFile (std::string const& path, u64 id)
	{
		std::vector<std::string> tokens;
		size_t depth = splitString(path, "/", tokens);

		addFile(tokens, id);
	}

	void addFile (std::vector<std::string> path, u64 id)
	{
		size_t depth = path.size();
		if(depth > 1) {
			findAndAdd(path.front(),
				std::vector<std::string>(
						path.begin()+1,
						path.end()
					), id);
		} else if(depth == 1) {
			files_.push_back(TreeEntry(path.back(), id));
		}
	}

	void findAndAdd (std::string const& name,
		std::vector<std::string> path, u64 id)
	{
		auto findChild = [&name] (TreeLeaf const& leaf)
		{
			return (leaf.name == name);
		};

		auto found = std::find_if(
			std::begin(leaves_), 
			std::end(leaves_),
			findChild);

		FileTree* child;

		if(found != std::end(leaves_)) {
			child = found->tree.get();
		} else {
			leaves_.push_back(TreeLeaf(name, new FileTree)); 
			child = leaves_.back().tree.get();
		}

		child->addFile(path, id);
	}
	
	void write (io::CWriteFile& target)
	{	
#if 0
		u32 id = 't' + ('r' << 8) + ('e' << 16) + ('e' << 24);
		u32 version = 1;

		archive_.write(&id,4);
		archive_.write(&version,4);
		
		u64 pointers = target.tell();

		// Reserve space for pointers
		u64 entries_ptr;
		u64 subtree_ptr;
		target.write(&entries_ptr,8);
		target.write(&subtree_ptr,8);

		writeTree();
#endif
	}

	u64 writeTree(io::CWriteFile& target)
	{
#if 0
		if(leaves_.size() > 0) {
			for(leaf : leaves_)
			{
				u64 offset = leaf.tree->writeTree();
				leaf.position = offset;
			}
		} else {
			
		}

		u64 actual_pos;

		entries_ptr = target.tell();
		for(file : files_) {
			target.write(file->first.c_str(),file->first.size());
			target.write(&file->second,8);
		}

		subtree_ptr = target.tell();

		// write pointers
		target.seek(pointers);
		target.write(&entries_ptr,8);
		target.write(&subtree_ptr,8);
		target.seek(subtree_ptr);

		// Reserve space
		for(leaf : leaves_) {
			target.write(leaf->first.c_str(),leaf->first.size());
			target.write(&subtree_ptr,8);
		}

		for(size_t id = 0; id < leaves_.size(); ++id) {
			leaves_[id].write(target);

		}
#endif
		return 0;
	}
};

} // namespace itd
} // namespace hrengin
#endif//_hrengin_CItdFileTree_
