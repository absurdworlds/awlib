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
{
	archive_.open(archive_name, std::ifstream::binary);

}

std::vector<std::string> ItdReader::list(std::string prefix)
{
	HPKTreeReader reader(archive_);

	archive_.seekg(0x40);
	u64 ptr;
	u64 size;

	archive_.read((char *)&ptr, 8);
	archive_.read((char *)&size, 8);

	archive_.seekg(ptr);

	reader.read();

	return reader.list(prefix);
}

std::vector<u8> ItdReader::getFileContents (u64 fileId)
{

}

std::vector<u8> ItdReader::getFileContents (std::string path)
{
}

} // namespace itd
} // namespace aw
