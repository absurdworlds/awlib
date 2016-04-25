/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_VisNode_
#define _aw_VisNode_

#include <aw/scene/SceneNode.h>

namespace aw {
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
} // namespace aw
#endif//_aw_VisNode_
