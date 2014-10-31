/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IEntityNode_
#define _hrengin_IEntityNode_
#include <hrengin/scene/IEntityNode.h>

namespace hrengin {
class IEntity;
namespace scene {

class CEntityNode : IEntityNode {
public:
	CEntityNode(IEntity* entity);
	virtual ~CEntityNode();
private:
};

} // namespace scene
} // namespace hrengin
#endif//_hrengin_IEntityNode_
