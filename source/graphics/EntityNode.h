/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_EntityNode_
#define _aw_EntityNode_
#include <aw/scene/EntityNode.h>

namespace aw {
class Entity;
namespace scene {

class EntityNode : EntityNode {
public:
	EntityNode(Entity* entity);
	virtual ~EntityNode();
private:
};

} // namespace scene
} // namespace aw
#endif//_aw_EntityNode_
