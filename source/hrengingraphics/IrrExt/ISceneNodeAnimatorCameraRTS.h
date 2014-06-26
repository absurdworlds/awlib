
// This is an extension for the "Irrlicht Engine".
// See copyright notice in irrlicht.h

#ifndef __I_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__
#define __I_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__


namespace irr
{

namespace scene
{
	class ISceneNodeAnimator;

	//! A scene node animator for RTS-style camera

	class ISceneNodeAnimatorCameraRTS : public ISceneNodeAnimator
	{
	public:

		//! Returns the speed of movement
		virtual f32 getMoveSpeed() const = 0;

		//! Sets the speed of movement
		virtual void setMoveSpeed(f32 moveSpeed) = 0;

		//! Returns the rotation speed
		virtual f32 getRotateSpeed() const = 0;

		//! Set the rotation speed
		virtual void setRotateSpeed(f32 rotateSpeed) = 0;

		//! Returns the zoom speed
		virtual f32 getZoomSpeed() const = 0;

		//! Set the zoom speed
		virtual void setZoomSpeed(f32 zoomSpeed) = 0;

		//! Returns the camera zoom
		virtual f32 getZoom() const = 0;

		//! Set the camera zoom
		virtual void setZoom(f32 multiplier) = 0;

		//! Returns the current distance, i.e. orbit radius
		virtual f32 getDistance() const = 0;

		//! Set the distance
		virtual void setDistance(f32 dist) = 0;
		
		//! Get the camera angle
		virtual f32 getAngle() const = 0;

		//! Set the camera angle
		virtual void setAngle(f32 a) = 0;

		//! Get the camera angle for close zoom
		virtual f32 getAngleClose() const = 0;

		//! Set the camera angle
		virtual void setAngleClose(f32 a) = 0;


		//! Sets the keyboard mapping for this animator (old style)
		//virtual void setKeyMap(SRTSKeyMap *map, u32 count) = 0;

		//! Sets the keyboard mapping for this animator
		//virtual void setKeyMap(const core::array<SRTSKeyMap>& keymap) = 0;

		//! Gets the keyboard mapping for this animator
		//virtual const core::array<SRTSKeyMap>& getKeyMap() const = 0;
	};

} // end namespace scene
} // end namespace irr

#endif //__I_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__

