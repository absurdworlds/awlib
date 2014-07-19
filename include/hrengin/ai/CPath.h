#ifndef __HRENGIN_CPath_H__
#define __HRENGIN_CPath_H__

#include <vector>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class CPath
{
public:
	std::vector<Vector3d> pathData_;
};

}
}

#endif//__HRENGIN_CPath_H__