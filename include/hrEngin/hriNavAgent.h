
#ifndef __HR_I_NAV_AGENT__
#define __HR_I_NAV_AGENT__

#include <hriPathfinder.h>

namespace hrengin
{
namespace ai
{

enum hreNAState
{
	NA_STATE_IDLE,
	NA_STATE_GUARD,
	NA_STATE_MOVETO,
	NA_STATE_FOLLOW,
	NA_STATE_AVOID,
	NA_STATE_GIVEWAY,
	NA_STATE_BLOCKWAY,
	NA_STATE_ATTACHED,
	NA_STATE_COUNT,
	NA_STATE_ = 0x7FFFFFFF //force 32 bit for byte-alignment
};

class hriNavAgent
{
	public:
		virtual ~hriNavAgent() {};
		virtual void SetPathfinder(hriPathfinder* pathfinder) = 0;
		virtual bool CheckState(hreNAState state) = 0;
		virtual hreNAState GetState() = 0;
		virtual void Move() = 0;
		virtual void Stop() = 0;
		virtual void Follow() = 0;
		virtual void AttachToGroup() = 0;
	private:
};

} // namespace ai
} // namespace hrengin

#endif //__HR_I_NAV_AGENT__