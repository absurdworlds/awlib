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
class IObject;

//! A node in the scene graph
class INode {
public:
	//! Default constructor
	INode ()
		: parent_(0)
	{
	}

	//! Construct attached to node
	INode (INode* parent)
	{
		parent->addChild(this);
	}

	virtual ~INode ()
	{
		for(auto it = children_.begin();
			 it != children_.end(); ++it) {
			(*it)->parent_ = 0;
			(*it)->onParentRemove();
		}
	}
	
	//! Attach child to node
	virtual bool addChild (INode* child)
	{
		if(std::find(children_.begin(), children_.end(), child) != children_.end()) {
			return false;
		}

		child->parent_ = this;
		children_.push_back(child);
		return true;
	}
	
	//! Remove child from node
	virtual bool removeChild (INode* child)
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
	virtual bool setParent (INode* parent)
	{
		if(parent_) {
			unparent();
		}

		return parent->addChild(this);
	}

	//! Detach node from parent
	virtual bool unparent ()
	{
		return parent_->removeChild(this);
	}

	//! Callback to be called on parent removal
	virtual void onParentRemove ()
	{

	}

	//! Set node's position via vector
	virtual void setPosition (Vector3d<f32> pos)
	{
		position_.set(pos);
	}
	
	//! Set node's position via coordinates
	virtual void setPosition (f32 const X, f32 const Y, f32 const Z)
	{
		position_.set(X, Y, Z);
	}

	// TODO: rename to 'setOrientation'
	//! Set node's orientation via euler angles
	virtual void setRotation (Vector3d<f32> euler)
	{
		rotation_ = euler;
	}
	
	//! Set node's orientation via quaternion
	virtual void setOrientation (Quaternion<f32> const& quat)
	{
	
	}

	//! Set node's relative scale
	virtual void setScale (Vector3d<f32> scale)
	{
	}
	
	//! Get node's position
	virtual Vector3d<f32> getPosition ()
	{
		return position_;
	}

	//! Get node's orientation
	virtual Vector3d<f32> getRotation ()
	{
		return rotation_;
	}

	//! Calculate node's absolute transform
	virtual Matrix4<f32> calculateAbsoluteTransform ()
	{
		Vector3d<f32> rot = getRotation() * math::RadiansInDegree;
		Vector3d<f32> pos = getPosition();

		f32 cp = cosf(rot[0]);
		f32 sp = sinf(rot[0]);
		f32 cy = cosf(rot[1]);
		f32 sy = sinf(rot[1]);
		f32 cr = cosf(rot[2]);
		f32 sr = sinf(rot[2]);

		Matrix4<f32> trans(
			cy*cp,	-cy*sp*cr + sy*sr,  cy*sp*sr + sy*cr,	pos[0],
			sp,	 cp*cr,		   -cp*sr,		pos[1],
			-sy*cp,	 sy*sp*cr + cy*sr, -sy*sp*sr + cy*cr,	pos[2],
			0,	 0,		    0,			1);
		return parent_ ?
			trans * parent_->calculateAbsoluteTransform() :
			trans;
	}
	
	//virtual void attachObject (IObject* object) = 0;
	//virtual void detachObject () = 0;
private:
	//! List of children of this node
	std::vector<INode*> children_;

	//! Pointer to the parent node
	INode* parent_;

	Vector3d<f32> position_;
	//! TODO: Replace with quaternion
	Vector3d<f32> rotation_;
};

//! temporary typedef for backwards compatibility
using ISceneNode = INode;

} // namespace scene
} // namespace hrengin

#endif //_hrengin_ISceneNode_
