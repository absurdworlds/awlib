#ifndef _hrengin_IVertexBuffer_
#define _hrengin_IVertexBuffer_

#include <hrengin/common/types.h>

namespace hrengin {
namespace video {

class SVertex;

class IVertexBuffer {
public:
	virtual SVertex& operator[] (const u32 index) = 0;

	virtual void push_back(const SVertex& vertex) = 0;
	virtual u32 size() const = 0;
};

	
} // namespace video
} // namespace hrengin

#endif//_hrengin_IVertexBuffer_
