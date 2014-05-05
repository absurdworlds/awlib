
#include "hrcVisNode.h"

namespace hrengin
{
namespace graphics
{
	
//! default constructor
//!
hrcVisNode::hrcVisNode()
{

}

//! default constructor
//! Attaches node to entity
hrcVisNode::hrcVisNode(hriBaseEntity* attach)
	: AttachedTo(attach)
{
	
}

void hrcVisNode::AttachToEntity(hriBaseEntity* attach)
{

}

u8 hrcVisNode::AddMesh(char * meshname)
{
	return 5;
}

void hrcVisNode::RemoveMesh(u8 meshslot)
{
}

void hrcVisNode::ReplaceMesh(u8 meshslot, char * meshname)
{
}

	
} // namespace graphics
} // namespace hrengin