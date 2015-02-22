/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_EntityNode_
#define _hrengin_EntityNode_
#include <hrengin/scene/EntityNode.h>

namespace hrengin {
class Entity;
namespace scene {

class EntityNode : EntityNode {
public:
	EntityNode(Entity* entity);
	virtual ~EntityNode();
private:
};

} // namespace scene
} // namespace hrengin
#endif//_hrengin_EntityNode_
