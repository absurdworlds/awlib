#ifndef __hrengin_IVertexListPrimitive__
#define __hrengin_IVertexListPrimitive__

#include <hrengin/common/hrengintypes.h>
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

#endif//__hrengin_IVertexListPrimitive__