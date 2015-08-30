/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_VisNode_
#define _awrts_VisNode_

#include <awrts/scene/SceneNode.h>

namespace awrts {
namespace graphics {
class Mesh;
}

namespace scene {
/*! Scene node, representing a visual object
 * Various renderables can be attached to it
 */
class VisNode : public Node {
public:
	virtual void setMesh(char const* mesh) = 0;
};

} // namespace scene
} // namespace awrts
#endif//_awrts_VisNode_
