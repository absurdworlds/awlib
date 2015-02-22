/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_VertexListPrimitive_
#define _hrengin_VertexListPrimitive_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/graphics/Renderable.h>

namespace hrengin {
namespace video {

class VertexListPrimitive : IRenderable {
public:
	// temporary — replace with vertex buffer later
	virtual void addVertex(Vectorf3d pos, u32 idx) = 0;
};

	
} // namespace video
} // namespace hrengin
#endif//_hrengin_VertexListPrimitive_
