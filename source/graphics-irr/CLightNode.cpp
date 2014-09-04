
#include "CVideoManager.h"

#include "CLightNode.h"

namespace hrengin{
namespace graphics{

CLightNode::CLightNode(CSceneManager* sceneManager,
	irr::scene::ILightSceneNode* lightNode)
	: node_(lightNode)
{

}

void CLightNode::setParentEntity(IBaseEntity* parent)
{

}

void CLightNode::setPosition(Vector3d<f32> pos)
{

}
void CLightNode::setRotation(Vector3d<f32> rot)
{

}
}
}