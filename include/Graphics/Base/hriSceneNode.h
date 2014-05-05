
#ifndef __HG_hriSceneNode__
#define __HG_hriSceneNode__


namespace hrengin
{

class hriBaseEntity;

namespace graphics
{
	

class hriSceneNode
{
	public:
		virtual void AttachToEntity(hriBaseEntity* attach) = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hriSceneNode__