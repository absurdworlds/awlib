
#include <algorithm>

#include <hrengin/common/types.h>
#include <hrengin/core/hrenginfsutil.h>

namespace hrengin {
namespace io {

std::string getFileExtension(std::string& dest, const std::string& path)
{
	u32 extpos = path.find_last_of(".");

	if(extpos == std::string::npos) {
		dest = "";
	}

	dest = path.substr(extpos+1);

	std::transform(dest.begin(), dest.end(), dest.begin(), ::tolower);

	return dest;
}

}
}