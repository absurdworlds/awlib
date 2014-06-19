#ifndef __H_INCLUDED__HRENGIN_IThinking
#define __H_INCLUDED__HRENGIN_IThinking

#include <hrengin/common/hrengintypes.h>
#include <hrengin/entities/IBaseEntity.h>

namespace hrengin {

class IThinking : public IBaseEntity
{
public:
	virtual void think(u32 time) = 0;
};
} //end namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IThinking