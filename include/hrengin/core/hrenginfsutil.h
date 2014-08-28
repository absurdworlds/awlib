#ifndef _hrengin_fsutil_
#define _hrengin_fsutil_

#include <string>

#include <hrengin/common/api.h>

namespace hrengin {
namespace io {

HRENGINFILESYSTEM_API std::string getFileExtension(std::string& dest, const std::string& path);

}
}

#endif  _hrengin_fsutil_