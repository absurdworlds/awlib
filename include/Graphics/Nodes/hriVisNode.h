
#ifndef __HG_hriVisNode__
#define __HG_hriVisNode__

#include <Base/hrTypes.h>
#include <Graphics/Base/hriSceneNode.h>

namespace hrengin
{
namespace graphics
{
	

class hriVisNode : public hriSceneNode
{
	public:
		virtual u8 AddMesh(char * meshname) = 0;
		virtual void RemoveMesh(u8 meshslot) = 0;
		virtual void ReplaceMesh(u8 meshslot, char * meshname) = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hriVisNode__