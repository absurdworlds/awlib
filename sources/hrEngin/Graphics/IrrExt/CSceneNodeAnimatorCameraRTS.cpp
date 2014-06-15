
// This is an extension for the "Irrlicht Engine".
// See copyright notice in irrlicht.h

#include "math.h"

#include <hrengin/config/hrConfig.h>

#include "CSceneNodeAnimatorCameraRTS.h"

namespace irr
{
namespace scene
{
	
	CSceneNodeAnimatorCameraRTS::CSceneNodeAnimatorCameraRTS(gui::ICursorControl* cursor, ITimer* timer, f32 distance, f32 angle, f32 angle_close, 
		f32 translateSpeed, f32 rotateSpeed, f32 zoomSpeed) 
		: CursorControl(cursor), lasthit(0.0f, 0.0f, 0.0f), mousepos(0,0), mousepos_old(0,0),
		  Timer(timer), ZoomSpeed(zoomSpeed), RotateSpeed(rotateSpeed), TranslateSpeed(translateSpeed),
		  Zooming(false), Rotating(false), Scrolling(false), Scroll_lock(true), Dragging(false),
		  MinZoom(0.2f), MaxZoom(5.f), NewZoom(1.0f), CurrentZoom(1.0f), RotZ(0.0f),
		  distance(distance), angle(angle), angle_close(angle_close), FirstUpdateReceived(false)

	{
		#ifdef _DEBUG
			//fprintf(stderr, "DEBUG: function call %s\n", __FUNCTION_NAME__);
		#endif //_DEBUG

		if (CursorControl)
		{
			CursorControl->grab();
			//MousePos = CursorControl->getRelativePosition();
		}

		allKeysUp();

		// create default key map
		/*KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_POS_X, irr::KEY_KEY_W));
		KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_POS_Y, irr::KEY_KEY_A));
		KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_NEG_X, irr::KEY_KEY_S));
		KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_NEG_Y, irr::KEY_KEY_D));
		KeyMap.push_back(SRTSKeyMap(EKA_MOVEMENT_CONTROLS, irr::KEY_MENU));*/
	}

	//! destructor
	CSceneNodeAnimatorCameraRTS::~CSceneNodeAnimatorCameraRTS()
	{
		if (CursorControl)
		{
			CursorControl->drop();
		}
	}

	bool CSceneNodeAnimatorCameraRTS::OnEvent(const SEvent& event)
	{
		//if (event.EventType != EET_MOUSE_INPUT_EVENT)
		//	return false;


		switch(event.EventType)
		{
		case EET_MOUSE_INPUT_EVENT:
			switch(event.MouseInput.Event)
			{
			case EMIE_RMOUSE_PRESSED_DOWN:
				MouseKeys[1] = true;
				break;
			case EMIE_RMOUSE_LEFT_UP:
				MouseKeys[1] = false;
				break;
			case EMIE_MOUSE_MOVED:
				mousepos = CursorControl->getPosition();
				break;
			case EMIE_MOUSE_WHEEL:
				NewZoom -= event.MouseInput.Wheel * ZoomSpeed * (CurrentZoom / (MaxZoom * MinZoom));
				break;
			/*case EMIE_LMOUSE_PRESSED_DOWN:
				break;
			case EMIE_MMOUSE_PRESSED_DOWN
			case EMIE_MMOUSE_LEFT_UP:
			case EMIE_LMOUSE_LEFT_UP:
			case EMIE_LMOUSE_DOUBLE_CLICK:
			case EMIE_RMOUSE_DOUBLE_CLICK:
			case EMIE_MMOUSE_DOUBLE_CLICK:
			case EMIE_LMOUSE_TRIPLE_CLICK:
			case EMIE_RMOUSE_TRIPLE_CLICK:
			case EMIE_MMOUSE_TRIPLE_CLICK:
			case EMIE_COUNT:*/
			default:
				return false;
			}

			break;
			
		case EET_KEY_INPUT_EVENT:		
			/*for (u32 i=0; i<KeyMap.size(); ++i)
			{
				if (KeyMap[i].KeyCode == event.KeyInput.Key)
				{
					CursorKeys[KeyMap[i].Action] = event.KeyInput.PressedDown;
					return true;
				}
			}

			break;*/

		default:
			return false;
		}
		return true;
	}
	
	bool CSceneNodeAnimatorCameraRTS::isMouseKeyDown(s32 key) const
	{
		return MouseKeys[key];
	}
	

	void CSceneNodeAnimatorCameraRTS::allKeysUp()
	{
		for (s32 i=0; i<3; ++i)
			MouseKeys[i] = false;
	}
	
	//! OnAnimate() is called just before rendering the whole scene.
	void CSceneNodeAnimatorCameraRTS::animateNode(ISceneNode *node, u32 timeMs)
	{
		// Controls :
		// Alt + WSAD = move camera
		// Mouse middle + Mouse move = move camera
		// Mouse pointer X/Y at border  = move camera
		// Mouse wheel up/down = zoom camera

		if (!node || node->getType() != ESNT_CAMERA)
		{
			return;
		}
		
		ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);

		// If the camera isn't the active camera, and receiving input, then don't process it.
		if (!camera->isInputReceiverEnabled())
		{
			return;
		}

		scene::ISceneManager * scnmgr = camera->getSceneManager();
		if (scnmgr && scnmgr->getActiveCamera() != camera)
		{
			return;
		}

		scene::ISceneCollisionManager* colman = scnmgr->getSceneCollisionManager();

		if (!CursorControl)
		{
			return;
		}
		
		core::dimension2d<u32> screen = scnmgr->getVideoDriver()->getScreenSize();

		if(!FirstUpdateReceived)
		{
			LastUpdate = Timer->getTime();
			FirstUpdateReceived = true;

			return;
		}
		
		u32 TimeDelta = LastUpdate;
		LastUpdate = Timer->getTime();
		TimeDelta = LastUpdate - TimeDelta;
		
		// Camera movement
		core::vector3df pos = camera->getPosition();
		core::vector3df target = camera->getTarget();

		core::vector3df translate(0,0,0);
		

		//core::vector3df zoom_close(0,20,30);
		//core::vector3df zoom_point(0,0,0);
		
		
		core::plane3df plane;

		core::line3df ray_new = colman->getRayFromScreenCoordinates(mousepos, camera);

		core::vector3df pos_new;

		plane.getIntersectionWithLine(ray_new.start, ray_new.getVector(), pos_new);

		if(isMouseKeyDown(MOUSE_KEY_MIDDLE) && !Zooming) //&& !Translating)
		{
			Dragging = true;
			
			if(mousepos_old != mousepos)
			{
				core::line3df ray_new = colman->getRayFromScreenCoordinates(mousepos, camera);
				core::line3df ray_old = colman->getRayFromScreenCoordinates(mousepos_old, camera);

				core::vector3df pos_old;
				core::vector3df pos_new;

				plane.getIntersectionWithLine(ray_old.start, ray_old.getVector(), pos_old);
				plane.getIntersectionWithLine(ray_new.start, ray_new.getVector(), pos_new);

				translate.X += pos_old.X - pos_new.X;
				translate.Z += pos_old.Z - pos_new.Z;
				
			}
			
			
			if ((mousepos.X < 5) || (mousepos.X > (screen.Width - 5)) || (mousepos.Y < 5) || (mousepos.Y > (screen.Height - 5)))
			{
				Scroll_lock = true;
			}
		}
		else
		{
			Dragging = false;

			if ((mousepos.X < 5) || (mousepos.X > (screen.Width - 5)) || (mousepos.Y < 5) || (mousepos.Y > (screen.Height - 5)))
			{
				Scroll_lock = false;
			}
		}
		mousepos_old = mousepos;
		
		if(NewZoom >= MaxZoom)
		{
			NewZoom = MaxZoom;
		}
		else if(NewZoom <= MinZoom)
		{
			NewZoom = MinZoom;
		}

		if(CurrentZoom != NewZoom && !Dragging && !Scrolling)
		{
			CurrentZoom = NewZoom;
			Zooming = true;
		}
		else
		{
			NewZoom = CurrentZoom;
			Zooming = false;
		}
		

		if(!Scroll_lock && !Dragging && !Zooming)
		{
			if ((mousepos.X < 5) && (mousepos.X > 0))   //Up
			{	
				translate.X += TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			}
			else if ((mousepos.X > (screen.Width - 5)) && (mousepos.X < screen.Width)) //Down
			{
				translate.X -= TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			}
			
			if ((mousepos.Y < 5) && (mousepos.Y > 0))   //Up
			{
				translate.Z -= TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			}
			else if ((mousepos.Y > (screen.Height - 5)) && (mousepos.Y < screen.Height)) //Down
			{
				translate.Z += TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			}
			
			if(translate.X + translate.Y == 0)
			{
				Scrolling = false;
			}
			else
			{
				Scrolling = true;
			}
		}

		f32 cur_angle;

		if(CurrentZoom < 1.f)
		{
			f32 relativeZoom = (CurrentZoom - MinZoom)/(1.f - MinZoom);
			cur_angle = angle * relativeZoom + angle_close * (1-relativeZoom);
		}
		else
		{
			cur_angle = angle;
		}

		cur_angle = angle;
		

		target += translate; 

		core::vector3df camera_offset(0,distance*sin(cur_angle),distance*cos(cur_angle));
		pos = target + camera_offset * CurrentZoom;
		
		/*target -=pos_new;
		pos -=pos_new;

		if(Zooming)
		{
			target /= CurrentZoom;
			pos /= CurrentZoom;
		fprintf(stderr, "DEBUG: ÷ðþþì-þþþì\n", target.X);
		}

		target +=pos_new;
		pos +=pos_new;*/

		camera->setPosition(pos);
		camera->setTarget(target);
	}

	//! Returns the speed of movement
	f32 CSceneNodeAnimatorCameraRTS::getMoveSpeed() const
	{
		return TranslateSpeed;
	}

	//! Sets the speed of movement
	void CSceneNodeAnimatorCameraRTS::setMoveSpeed(f32 speed)
	{
		TranslateSpeed = speed;
	}

	//! Returns the rotation speed
	f32 CSceneNodeAnimatorCameraRTS::getRotateSpeed() const
	{
		return RotateSpeed;
	}

	//! Set the rotation speed
	void CSceneNodeAnimatorCameraRTS::setRotateSpeed(f32 speed)
	{
		RotateSpeed = speed;
	}

	//! Returns the zoom speed
	f32 CSceneNodeAnimatorCameraRTS::getZoomSpeed() const
	{
		return ZoomSpeed;
	}

	//! Set the zoom speed
	void CSceneNodeAnimatorCameraRTS::setZoomSpeed(f32 speed)
	{
		ZoomSpeed = speed;
	}

	//! Returns the camera zoom
	f32 CSceneNodeAnimatorCameraRTS::getZoom() const
	{
		return CurrentZoom;
	}

	//! Set the camera zoom
	void CSceneNodeAnimatorCameraRTS::setZoom(f32 multiplier)
	{
		if(multiplier < MaxZoom)
		{
			CurrentZoom = MaxZoom;
		}
		else if(multiplier > MinZoom)
		{
			CurrentZoom = MinZoom;
		}
		else			
		{
			CurrentZoom = multiplier;
		}
	}

	//! Returns the current distance, i.e. orbit radius
	f32 CSceneNodeAnimatorCameraRTS::getDistance() const
	{
		return distance;
	}

	//! Set the distance
	void CSceneNodeAnimatorCameraRTS::setDistance(f32 dist)
	{
		distance = dist;
	}
		
	//! Get the camera angle
	f32 CSceneNodeAnimatorCameraRTS::getAngle() const
	{
		return angle;
	}

	//! Set the camera angle
	void CSceneNodeAnimatorCameraRTS::setAngle(f32 a)
	{
		angle = a;
	}

	//! Get the camera angle for close zoom
	f32 CSceneNodeAnimatorCameraRTS::getAngleClose() const
	{
		return angle_close;
	}

	//! Set the camera angle
	void CSceneNodeAnimatorCameraRTS::setAngleClose(f32 a)
	{
		angle_close = a;
	}


	ISceneNodeAnimator* CSceneNodeAnimatorCameraRTS::createClone(ISceneNode* node, ISceneManager* newManager)
	{
		CSceneNodeAnimatorCameraRTS * newAnimator =
			new CSceneNodeAnimatorCameraRTS(CursorControl, Timer, RotateSpeed, ZoomSpeed, TranslateSpeed);
		return newAnimator;
	}

	
	/*//! Sets the keyboard mapping for this animator
	void CSceneNodeAnimatorCameraFPS::setKeyMap(SKeyMap *map, u32 count)
	{
		// clear the keymap
		KeyMap.clear();

		// add actions
		for (u32 i=0; i<count; ++i)
		{
			KeyMap.push_back(map[i]);
		}
	}

	void CSceneNodeAnimatorCameraFPS::setKeyMap(const core::array<SKeyMap>& keymap)
	{
		KeyMap=keymap;
	}

	const core::array<SKeyMap>& CSceneNodeAnimatorCameraFPS::getKeyMap() const
	{
		return KeyMap;
	}*/

} // end namespace scene
} // end namespace irr
