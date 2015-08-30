/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_EntityNode_
#define _awrts_EntityNode_
#include <awrts/scene/EntityNode.h>

namespace awrts {
class Entity;
namespace scene {

class EntityNode : EntityNode {
public:
	EntityNode(Entity* entity);
	virtual ~EntityNode();
private:
};

} // namespace scene
} // namespace awrts
#endif//_awrts_EntityNode_
