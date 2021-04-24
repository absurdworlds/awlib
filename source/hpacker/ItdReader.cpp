/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "ItdReader.h"
#include "HPKTreeReader.h"

namespace aw {
namespace itd {
ItdReader::ItdReader(std::istream& archive, bool verbose)
	: archive(archive)
	, reader(std::make_unique<HPKTreeReader>(archive))
{
	archive.seekg(0x40);
	u64 ptr;
	u64 size;

	archive.read((char *)&ptr, 8);
	archive.read((char *)&size, 8);

	archive.seekg(ptr);

	reader->read();
}

std::vector<std::string> ItdReader::list(std::string prefix)
{
	return reader->list(prefix);
}

std::vector<u8> ItdReader::getFileContents(u64 fileId)
{
	archive.seekg(0x40 + 16*fileId);
	u64 ptr;
	u64 size;
	archive.read((char *)&ptr, 8);
	archive.read((char *)&size, 8);

	archive.seekg(ptr);

	std::vector<u8> tmp(size,0);
	archive.read((char*)tmp.data(), size);
	return tmp;
}

std::vector<u8> ItdReader::getFileContents(std::string path)
{
	return getFileContents(reader->findFile(path));
}

} // namespace itd
} // namespace aw
