/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <algorithm>

#include <aw/utility/string/string.h>

#include "HPKTreeWriter.h"

namespace aw {
namespace itd {
HPKTreeWriter::HPKTreeWriter ()
{
}

HPKTreeWriter::~HPKTreeWriter ()
{
}

void HPKTreeWriter::addFile (std::string const& path, u64 id)
{
	std::vector<std::string> dir;
	std::string name;

	dir = string::split(path, "/");
	name = dir.back();
	dir.pop_back();

	root_.add(dir, name, id, strings_);
}

void HPKTreeWriter::write (std::ostream& target)
{
        u64 baseOffset = 32;
        root_.calcOffsets(baseOffset);

        Header header;
	target.write((char *)&header.type,4);
	target.write((char *)&header.unused,4);

	target.write((char *)&root_.filesPtr, 8);
	target.write((char *)&root_.filesNum, 4);
	target.write((char *)&root_.subtreePtr, 8);
	target.write((char *)&root_.subtreeNum, 4);

	root_.writeOut(target, baseOffset);
	strings_.putStrings(target);
}

void TreeNode::add (std::vector<std::string> path, std::string name, u64 id,
		StringBank & strings)
{
	if(path.empty()) {
		u64 nameOffset = strings.add(name);
		files.push_back(ListEntry(nameOffset, id));
		return;
	}

	std::string dirName = path.front();

	auto findChild = [&dirName] (TreeNode const& leaf)
	{
		return (leaf.name == dirName);
	};

	auto dir = std::find_if(leaves.begin(), leaves.end(), findChild);

	if(dir == leaves.end()) {
		TreeNode leaf;
		leaf.name = path.front();
		leaf.nameOffset = strings.add(leaf.name);

		dir = leaves.insert(leaves.end(), leaf);
	}

	dir->add(std::vector<std::string>(path.begin()+1,path.end()),
			name, id, strings);
}

void TreeNode::calcOffsets (u64 & baseOffset)
{
	// Note: calcOffsets and writeOut can be combined together to 
	// reduce number of tree traversals, however, I left them as
	// they are now, for readability.
	// I leave this note, <s>because I tend to leave a lot of unnecessary
	// notes </s> so later this part will be rewritten.
	//
	filesPtr = baseOffset;
	filesNum = files.size();

	baseOffset += filesNum * 16;

	subtreePtr = baseOffset;
	subtreeNum = leaves.size();

	baseOffset += subtreeNum * 32;

	for(auto & node : leaves) {
		node.calcOffsets(baseOffset);
	}
}

void TreeNode::writeOut (std::ostream & target, u64 baseOffset)
{
	for(auto & file : files) {
		file.nameOffset += baseOffset;
		target.write((char *)&file.nameOffset, 8);
		target.write((char *)&file.id, 8);
	}

	for(auto & node : leaves) {
		node.nameOffset += baseOffset;
		target.write((char *)&node.nameOffset, 8);
		target.write((char *)&node.filesPtr, 8);
		target.write((char *)&node.filesNum, 4);
		target.write((char *)&node.subtreePtr, 8);
		target.write((char *)&node.subtreeNum, 4);
	}

	for(auto & node : leaves) {
		node.writeOut(target, baseOffset);
	}
}
} //namespace itd
} //namespace aw
