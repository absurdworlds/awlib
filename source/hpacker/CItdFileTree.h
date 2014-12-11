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
		u32 id = 't' + ('r' << 8) + ('e' << 16) + ('e' << 24);
		u32 version = 1;

		target.write(&id,4);
		target.write(&version,4);
		
		writeTree(target);
	}

	u64 writeTree(io::CWriteFile& target)
	{
		u64 pointers = target.tell();

		// Reserve space for pointers
		u64 entries_ptr = -1;
		u64 subtree_ptr = -1;
		target.write(&entries_ptr,8);
		target.write(&subtree_ptr,8);
		
		if(files_.size() > 0) {
			entries_ptr = target.tell();
			for(auto file : files_) {
				target.write(
					file.name.c_str(),
					file.name.size() + 1);
				target.write(&file.id,8);
			}
		}

		subtree_ptr = target.tell();

		// write pointers
		target.seek(pointers);
		if(files_.size() > 0) {
			target.write(&entries_ptr,8);
		}
		if(leaves_.size() > 0) {
			target.write(&subtree_ptr,8);
		}

		target.seek(subtree_ptr);
		if(leaves_.size() > 0) {
			// Reserve space
			for(auto&& leaf : leaves_) {
				target.write(
					leaf.name.c_str(),
					leaf.name.size() + 1);
				target.write(&leaf.position,8);
			}

			for(auto&& leaf : leaves_) {
				u64 offset = leaf.tree->writeTree(target);
				leaf.position = offset;
			}

			u64 last_pos = target.tell();

			target.seek(subtree_ptr);
			for(auto&& leaf : leaves_) {
				target.write(
					leaf.name.c_str(),
					leaf.name.size() + 1);
				target.write(&leaf.position,8);
			}
			target.seek(last_pos);
		}

		return pointers;
	}
};

} // namespace itd
} // namespace hrengin
#endif//_hrengin_CItdFileTree_
