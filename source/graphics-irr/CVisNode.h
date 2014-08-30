#ifndef _hrengin_CVisNode_
#define _hrengin_CVisNode_

#include <hrengin/common/types.h>

#include <hrengin/graphics/IMesh.h>
#include <hrengin/graphics/IVisNode.h>

namespace irr {
namespace scene {
class IAnimatedMeshSceneNode;
}
}

namespace hrengin {
class IBaseEntity;

namespace graphics {
class CSceneManager;

class CVisNode : public IVisNode {
public:
	CVisNode(CSceneManager* sceneManager,
		irr::scene::IAnimatedMeshSceneNode* meshNode);

	virtual void setParentEntity(IBaseEntity* parent);

	virtual void setPosition(Vector3d pos);
	virtual void setRotation(Vector3d rot);
	//virtual void SetScale(Vectorf3d scale);

	//virtual void setMesh(IMesh* mesh);
	virtual void setMesh(const char* mesh);

private:
	CSceneManager* sceneManager_;
	IBaseEntity* parent_;

	irr::scene::IAnimatedMeshSceneNode* meshNode_;
};

	
} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CVisNode_
