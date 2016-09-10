/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <algorithm>

#include <aw/utility/string/split.h>

#include "HPKTreeReader.h"

namespace aw {
namespace itd {
HPKTreeReader::HPKTreeReader(std::istream& source)
	: source(source)
{
}

HPKTreeReader::~HPKTreeReader()
{
}

u64 HPKTreeReader::findFile(std::string const& path)
{
	return files[path];
}

std::vector<std::string> HPKTreeReader::list(std::string const& prefix)
{
	std::vector<std::string> results;
	
	auto it = files.lower_bound(prefix);

	while (it != files.end()) {
		std::string const& key = it->first;

		if (key.compare(0, prefix.size(), prefix) == 0) {
			results.push_back(key);
		}

		++it;
	}

	return results;
}

void HPKTreeReader::read()
{
	base = source.tellg();

	u32 tmp_junk;
	source.read((char *)&tmp_junk,4);
	source.read((char *)&tmp_junk,4);

	u64 files_ptr;
	u32 files_num;
	u64 subtree_ptr;
	u32 subtree_num;

	source.read((char *)&files_ptr, 8);
	source.read((char *)&files_num, 4);
	source.read((char *)&subtree_ptr, 8);
	source.read((char *)&subtree_num, 4);

	readFiles("/", files_ptr, files_num);
	readDirs("/", subtree_ptr, subtree_num);
}

std::string HPKTreeReader::loadString(u64 ptr)
{
	u64 pos = source.tellg();

	source.seekg(base + ptr);

	u16 size;
	source.read((char *)&size,2);

	std::string name(size, 0);
	source.read(&name.front(), size);

	source.seekg(pos);

	return name;
}

void HPKTreeReader::readFiles(std::string dir, u64 ptr, u64 num)
{
	u64 count = 0;

	source.seekg(base + ptr);

	while (count < num) {
		source.seekg(base + ptr + count*16);

		u64 nameOffset;
		u64 id;

		source.read((char *)&nameOffset, 8);
		source.read((char *)&id, 8);

		std::string path = std::move(loadString(nameOffset));

		// TODO: only if doesn't exist
		files[dir + path] = id;


		++count;
	}
}

void HPKTreeReader::readDirs(std::string dir, u64 ptr, u64 num)
{
	u64 count = 0;

	source.seekg(base + ptr);

	while (count < num) {
		source.seekg(base + ptr + count*32);

		u64 nameOffset;
		u64 files_ptr;
		u32 files_num;
		u64 subtree_ptr;
		u32 subtree_num;

		source.read((char *)&nameOffset, 8);
		source.read((char *)&files_ptr, 8);
		source.read((char *)&files_num, 4);
		source.read((char *)&subtree_ptr, 8);
		source.read((char *)&subtree_num, 4);

		std::string path = std::move(loadString(nameOffset));
		path = dir + path + "/";

		readFiles(path, files_ptr, files_num);
		readDirs(path, subtree_ptr, subtree_num);

		++count;
	}
}

} //namespace itd
} //namespace awrts
