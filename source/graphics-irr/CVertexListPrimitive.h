#ifndef __hrengin_CVertexListPrimitive__
#define __hrengin_CVertexListPrimitive__

#include <vector>

#include <hrengin/graphics/IVertexListPrimitive.h>
#include <hrengin/graphics/IVideoManager.h>

namespace hrengin {
namespace video {

class CVertexListPrimitive : IVertexListPrimitive
{
public:
	CVertexListPrimitive(graphics::IVideoManager* vmgr)
	: vmgr_(vmgr)
	{
	
	}

	virtual void render()
	{

	}

	virtual void addVertex(Vector3d<f32> pos, u32 idx)
	{
		vertixes_.push_back(pos);
		indexes_.push_back(idx);
	}

private:
	std::vector<Vector3d<f32>> vertixes_;
	std::vector<u32> indexes_;
	graphics::IVideoManager* vmgr_;
};

	
} // namespace video
} // namespace hrengin

#endif//__hrengin_CVertexListPrimitive__