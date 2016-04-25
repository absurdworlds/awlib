/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_ItdReader_
#define _aw_ItdReader_
#include <vector>
#include <fstream>
#include <memory>

#include <aw/common/types.h>
#include <aw/itd/HPKIndexReader.h>

namespace aw {
namespace itd {

class ItdReader {
public:
	ItdReader (std::string const& archive_name, bool verbose);

	std::vector<std::string> list (std::string prefix);

	std::vector<u8> getFileContents (u64 fileId);
	std::vector<u8> getFileContents (std::string path);
private:
	std::ifstream archive;
	std::unique_ptr<HPKIndexReader> reader;
};
} // namespace itd
} // namespace aw
#endif//_aw_ItdReadere_
