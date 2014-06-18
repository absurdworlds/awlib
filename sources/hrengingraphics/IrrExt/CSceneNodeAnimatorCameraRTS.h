
// This is an extension for the "Irrlicht Engine".
// See copyright notice in irrlicht.h

#ifndef __C_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__

#include "Irrlicht/irrlicht.h"
#include "ISceneNodeAnimatorCameraRTS.h"

namespace irr
{

namespace gui
{
	class ICursorControl;
}

namespace scene
{

	//! Scene node animator for RTS cameras
	class CSceneNodeAnimatorCameraRTS : public ISceneNodeAnimatorCameraRTS
	{
	public:

		//! Constructor
		CSceneNodeAnimatorCameraRTS(gui::ICursorControl* cursor, ITimer* timer, f32 distance=36.055, f32 angle=0.9828, f32 angle_close=0.5880, 
		f32 translateSpeed = 0.1f, f32 rotateSpeed = 0.1f, f32 zoomSpeed=0.1f);

		//! Destructor
		virtual ~CSceneNodeAnimatorCameraRTS();

		//! Animates the scene node, currently only works on cameras
		virtual void animateNode(ISceneNode* node, u32 timeMs);

		//! Event receiver
		virtual bool OnEvent(const SEvent& event);

		//! Returns the speed of movement
		virtual f32 getMoveSpeed() const;

		//! Sets the speed of movement
		virtual void setMoveSpeed(f32 moveSpeed);

		//! Returns the rotation speed
		virtual f32 getRotateSpeed() const;

		//! Set the rotation speed
		virtual void setRotateSpeed(f32 rotateSpeed);

		//! Returns the zoom speed
		virtual f32 getZoomSpeed() const;

		//! Set the zoom speed
		virtual void setZoomSpeed(f32 zoomSpeed);

		//! Returns the camera zoom
		virtual f32 getZoom() const;

		//! Set the camera zoom
		virtual void setZoom(f32 multiplier);

		//! Returns the current distance, i.e. orbit radius
		virtual f32 getDistance() const;

		//! Set the distance
		virtual void setDistance(f32 dist);
		
		//! Get the camera angle
		virtual f32 getAngle() const;

		//! Set the camera angle
		virtual void setAngle(f32 a);

		//! Get the camera angle for close zoom
		virtual f32 getAngleClose() const;

		//! Set the camera angle
		virtual void setAngleClose(f32 a);

		//! Sets the keyboard mapping for this animator (old style)
		//virtual void setKeyMap(SRTSKeyMap *map, u32 count);

		//! Sets the keyboard mapping for this animator
		//!	\param keymap The new keymap array 
		//virtual void setKeyMap(const core::array<SRTSKeyMap>& keymap);

		//! Gets the keyboard mapping for this animator
		//virtual const core::array<SRTSKeyMap>& getKeyMap() const;
		
		//! This animator will receive events when attached to the active camera
		virtual bool isEventReceiverEnabled() const
		{
			return true;
		}

		//! Returns the type of this animator
		virtual ESCENE_NODE_ANIMATOR_TYPE getType() const
		{
			return ESNAT_CAMERA_FPS;
		}
		
		//! Creates a clone of this animator.
		/** Please note that you will have to drop
		(IReferenceCounted::drop()) the returned pointer once you're
		done with it. */
		virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);

	private:
		void allKeysUp();
		void animate();
		bool isMouseKeyDown(s32 key) const;

		bool MouseKeys[3];
		//bool MouseMiddle;
		enum MOUSE_KEY
		{
			MOUSE_KEY_RIGHT,
			MOUSE_KEY_MIDDLE,
			MOUSE_KEY_LEFT
		};
		
		gui::ICursorControl *CursorControl;
		ITimer* Timer;
		
		bool FirstUpdateReceived;
		u32 LastUpdate;
		//scene::ICameraSceneNode* OldCamera;
		//core::vector3df OldTarget;
		//core::vector3df LastCameraTarget;	
		
		//core::array<SRTSKeyMap> KeyMap;

		/*core::position2df RotateStart;
		core::position2df ZoomStart;
		core::position2df TranslateStart;*/

		f32 distance;
		f32 angle;
		f32 angle_close;
		
		core::vector2di mousepos;
		core::vector2di mousepos_old;
		core::vector3df lasthit;

		//bool CursorKeys[EKA_RTS_COUNT];

		f32 ZoomSpeed;
		f32 RotateSpeed;
		f32 TranslateSpeed;
		
		f32 MinZoom;
		f32 NewZoom;
		f32 CurrentZoom;
		f32 MaxZoom;
		
		f32 RotZ;
		f32 MaxRotZ;

		//s32 LastAnimationTime;

		bool firstUpdate;
		//bool firstInput;

		bool Zooming;
		bool Rotating;
		bool Scrolling;
		bool Scroll_lock;
		bool Dragging;
	};

} // end namespace scene
} // end namespace irr

#endif//__C_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__