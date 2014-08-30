#ifndef _hrengin_IVertexListPrimitive_
#define _hrengin_IVertexListPrimitive_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/graphics/IRenderable.h>

namespace hrengin {
namespace video {

class IVertexListPrimitive : IRenderable
{
public:
	// temporary — replace with vertex buffer later
	virtual void addVertex(Vectorf3d pos, u32 idx) = 0;
};

	
} // namespace video
} // namespace hrengin

#endif//_hrengin_IVertexListPrimitive_
