/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IVisNode_
#define _hrengin_IVisNode_

#include <hrengin/scene/ISceneNode.h>

namespace hrengin {
namespace graphics {
class IMesh;
}

namespace scene {
/*! Scene node, representing a visual object
 * Various renderables can be attached to it
 */
class IVisNode : public INode {
public:
	virtual void setMesh(char const* mesh) = 0;
};

} // namespace scene
} // namespace hrengin
#endif//_hrengin_IVisNode_
