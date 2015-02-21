/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IEntitySceneNode_
#define _hrengin_IEntitySceneNode_

#include <hrengin/game/IEntity.h>

#include <hrengin/scene/ISceneNode.h>

namespace hrengin {
class IEntity;

namespace scene {
/*! This type of node represents a game entity
 * \see IEntity
 */
class IEntityNode : INode {
public:
};

} // namespace scene
} // namespace hrengin
#endif //_hrengin_IEntitySceneNode_
