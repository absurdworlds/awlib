/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "CItdReader.h"

namespace hrengin {
namespace itd {
CItdReader::CItdReader (io::CReadFile* archive)
	: archive_(archive)
{

}

std::vector<std::string> CItdReader::list (std::string prefix)
{
	
}

std::vector<u8> CItdReader::getFileContents (u64 fileId)
{
	
}

std::vector<u8> CItdReader::getFileContents (std::string path)
{
}

} // namespace itd
} // namespace hrengin
