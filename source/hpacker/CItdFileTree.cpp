/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <algorithm>

#include "CItdFileTree.h"

namespace hrengin {
namespace itd {

void FileTree::addFile (std::string const& path, u64 id)
{
	std::vector<std::string> tokens;
	size_t depth = splitString(path, "/", tokens);

	addFile(tokens, id);
}

void FileTree::addFile (std::vector<std::string> path, u64 id)
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

void FileTree::findAndAdd (std::string const& name,
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

void FileTree::write (std::ofstream& target)
{
	u32 id = 't' + ('r' << 8) + ('e' << 16) + ('e' << 24);
	u32 version = 1;

	target.write((char *)&id,4);
	target.write((char *)&version,4);
	
	writeTree(target);
}

u64 FileTree::writeTree (std::ofstream& target)
{
	u64 pointers = target.tellp();

	// Reserve space for pointers
	u64 last_pos;
	u64 entries_ptr = -1;
	u64 subtree_ptr = -1;
	target.write((char *)&entries_ptr,8);
	target.write((char *)&subtree_ptr,8);

	if(files_.size() > 0) {
		entries_ptr = target.tellp();
		for(auto const& file : files_) {
			target.write(
				file.name.c_str(),
				file.name.size() + 1);
			target.write((char *)&file.id,8);
		}
	}

	last_pos = target.tellp();

	if(leaves_.size() > 0) {
		subtree_ptr = last_pos;

		// Reserve space
		writeDirList(target);

		for(auto& leaf : leaves_) {
			u64 offset = leaf.tree->writeTree(target);
			leaf.position = offset;
		}
		
		// store position
		last_pos = target.tellp();

		// Wrtite actual list
		target.seekp(subtree_ptr);
		writeDirList(target);
	}

	// write pointers
	target.seekp(pointers);
	if(files_.size() > 0) {
		target.write((char *)&entries_ptr,8);
	}
	if(leaves_.size() > 0) {
		target.write((char *)&subtree_ptr,8);
	}
	target.seekp(last_pos);

	return pointers;
}

void FileTree::writeDirList (std::ofstream& target)
{
	for(auto const& leaf : leaves_) {
		target.write(
			leaf.name.c_str(),
			leaf.name.size() + 1);
		target.write((char *)&leaf.position,8);
	}
}
} // namespace itd
} // namespace hrengin
