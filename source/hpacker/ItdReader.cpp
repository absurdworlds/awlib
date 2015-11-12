/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "ItdReader.h"
#include "HPKTreeReader.h"

namespace aw {
namespace itd {
ItdReader::ItdReader(std::string const& archive_name, bool verbose)
	: reader(std::make_unique<HPKTreeReader>(archive))
{
	archive.open(archive_name, std::ifstream::binary);

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
