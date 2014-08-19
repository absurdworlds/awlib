#ifndef __HRENGIN_FILESYSTEM__hrenginfsutil_H__
#define __HRENGIN_FILESYSTEM__hrenginfsutil_H__

#include <string>

#include <hrengin/common/hrenginapi.h>

namespace hrengin {
namespace io {

HRENGINFILESYSTEM_API std::string getFileExtension(std::string& dest, const std::string& path);

}
}

#endif  __HRENGIN_FILESYSTEM__hrenginfsutil_H__