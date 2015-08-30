/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_VertexBuffer_
#define _awrts_VertexBuffer_

#include <awrts/common/types.h>

namespace awrts {
namespace graphics {

class Vertex;

class VertexBuffer {
public:
	virtual Vertex& operator[] (const u32 index) = 0;

	virtual void push_back(const SVertex& vertex) = 0;
	virtual u32 size() const = 0;
};

} // namespace video
} // namespace awrts
#endif//_awrts_VertexBuffer_
