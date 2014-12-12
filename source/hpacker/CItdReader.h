/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CItdReader_
#define _hrengin_CItdReader_
#include <vector>

#include <hrengin/common/types.h>
#include <hrengin/io/CReadFile.h>

namespace hrengin {
namespace itd {

class CItdReader {
public:
	CItdReader (io::CReadFile* archive);

	std::vector<std::string> list (std::string prefix);

	std::vector<u8> getFileContents (u64 fileId);
	std::vector<u8> getFileContents (std::string path);
private:
	io::CReadFile* archive_;
};
} // namespace itd
} // namespace hrengin
#endif//_hrengin_CItdReadere_
