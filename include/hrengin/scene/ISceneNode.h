/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISceneNode_
#define _hrengin_ISceneNode_

#include <vector>
#include <algorithm>

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Matrix4.h>
#include <hrengin/common/Quaternion.h>

namespace hrengin {
namespace scene {

//! A node in the scene graph
class ISceneNode {
public:
	virtual ~ISceneNode() 
	{
		for(auto it = children_.begin();
			 it != children_.end(); ++it) {
			
			(*it)->parent_ = 0;
			(*it)->onParentRemove();
		}
	}
	
	//! Attach child to node
	virtual bool addChild(ISceneNode* child)
	{
		if(std::find(children_.begin(), children_.end(), child) != children_.end()) {
			return false;
		}

		child->parent_ = this;
		children_.push_back(child);
		return true;
	}
	
	//! Remove child from node
	virtual bool removeChild(ISceneNode* child)
	{
		auto found = std::find(children_.begin(), children_.end(), child);
		if(found == children_.end()) {
			return false;
		}

		(*found)->parent_ = 0;
		std::iter_swap(found, children_.end() - 1);
		children_.pop_back();
		return true;
	}
	
	//! Attach node to parent
	virtual bool setParent(ISceneNode* parent)
	{
		if(parent_) {
			unparent();
		}

		return parent->addChild(this);
	}

	//! Detach node from parent
	virtual bool unparent()
	{
		return parent_->removeChild(this);
	}

	//! Callback to be called on parent removal
	virtual void onParentRemove()
	{

	}

	//! Set node's position via vector
	virtual void setPosition(Vector3d<f32> pos) = 0;
	
	//! Set node's position via coordinates
//	virtual void setPosition(f32 const X, f32 const Y, f32 const Z) = 0;

	//! Set node's orientation via euler angles
	virtual void setRotation(Vector3d<f32> euler) = 0;
	
	//! Set node's orientation via quaternion
	virtual void setOrientation(Quaternion<f32> const& quat) {};
	//virtual void setScale(Vector3d<f32> scale) = 0;
private:
	//! List of children of this node
	std::vector<ISceneNode*> children_;

	//! Pointer to the parent node
	ISceneNode* parent_;
};

} // namespace graphics
} // namespace hrengin

#endif //_hrengin_ISceneNode_
