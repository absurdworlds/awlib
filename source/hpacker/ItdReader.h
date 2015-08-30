/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_ItdReader_
#define _awrts_ItdReader_
#include <vector>
#include <fstream>

#include <awrts/common/types.h>
#include <awrts/itd/HPKIndexReader.h>

namespace awrts {
namespace itd {

class ItdReader {
public:
	ItdReader (std::string const& archive_name, bool verbose);

	std::vector<std::string> list (std::string prefix);

	std::vector<u8> getFileContents (u64 fileId);
	std::vector<u8> getFileContents (std::string path);
private:
	std::ifstream archive_;
};
} // namespace itd
} // namespace awrts
#endif//_awrts_ItdReadere_
