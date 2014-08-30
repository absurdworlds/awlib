#ifndef _hrengin_IVisNode_
#define _hrengin_IVisNode_

#include <hrengin/common/types.h>
#include <hrengin/graphics/ISceneNode.h>

namespace hrengin {
namespace graphics {
class IMesh;

class IVisNode : public ISceneNode {
public:
	virtual void setMesh(IMesh* mesh) = 0;
};

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_IVisNode_
