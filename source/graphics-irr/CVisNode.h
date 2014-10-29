/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CVisNode_
#define _hrengin_CVisNode_

#include <hrengin/common/types.h>

#include <hrengin/graphics/IMesh.h>
#include <hrengin/scene/IVisNode.h>

namespace irr {
namespace scene {
class IAnimatedMeshSceneNode;
}
}

namespace hrengin {
class IBaseEntity;

namespace scene {
class CSceneManager;

class CVisNode : public IVisNode {
public:
	CVisNode(CSceneManager* sceneManager,
		irr::scene::IAnimatedMeshSceneNode* meshNode);
	virtual ~CVisNode();

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);
	//virtual void SetScale(Vector3d<f32> scale);

	//virtual void setMesh(IMesh* mesh);
	virtual void setMesh(const char* mesh);

private:
	CSceneManager* sceneManager_;
	IBaseEntity* parent_;

	irr::scene::IAnimatedMeshSceneNode* meshNode_;
};

} // namespace scene
} // namespace hrengin

#endif//_hrengin_CVisNode_
