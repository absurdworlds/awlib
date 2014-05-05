
#ifndef __HR_I_PATH_FINDER__
#define __HR_I_PATH_FINDER__

#include "hrtpath.h"

namespace hrengin
{
namespace ai
{

class hriPathfinder
{
	public:
		virtual ~hriPathfinder() {}
		virtual path* CalculatePath() = 0;
	private:
};

} // namespace ai
} // namespace hrengin

#endif //__HR_I_PATH_FINDER__