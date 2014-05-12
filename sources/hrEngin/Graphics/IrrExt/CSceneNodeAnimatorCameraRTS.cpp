
// This is an extension for the "Irrlicht Engine".
// See copyright notice in irrlicht.h

#include "CSceneNodeAnimatorCameraRTS.h"
#include "math.h"
#include <Base/Config/hrConfig.h>

namespace irr
{
namespace scene
{
	
	CSceneNodeAnimatorCameraRTS::CSceneNodeAnimatorCameraRTS(gui::ICursorControl* cursor, ITimer* timer, f32 distance, f32 angle, f32 angle_close, 
		f32 translateSpeed, f32 rotateSpeed, f32 zoomSpeed) 
		: CursorControl(cursor), MousePos(0.5f, 0.5f), MousePos_old(0.5f, 0.5f), Timer(timer),
		ZoomSpeed(zoomSpeed), RotateSpeed(rotateSpeed), TranslateSpeed(translateSpeed),
	Zooming(false), Rotating(false), Scrolling(false), Scroll_lock(false), Dragging(false), 
	MinZoom(0.2f), MaxZoom(5.f), NewZoom(1.0f), CurrentZoom(1.0f), RotZ(0.0f),
	distance(distance), angle(angle), angle_close(angle_close), FirstUpdateReceived(false)

	{
		#ifdef _DEBUG
			fprintf(stderr, "DEBUG: function call %s\n", __FUNCTION_NAME__);
		#endif //_DEBUG

		if (CursorControl)
		{
			CursorControl->grab();
			MousePos = CursorControl->getRelativePosition();
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
			case EMIE_MMOUSE_PRESSED_DOWN:
				MouseKeys[1] = true;
				break;
			case EMIE_MMOUSE_LEFT_UP:
				MouseKeys[1] = false;
				break;
			case EMIE_MOUSE_MOVED:
				MousePos = CursorControl->getRelativePosition();
				MousePos2 = CursorControl->getPosition();
				break;
			case EMIE_MOUSE_WHEEL:
				NewZoom -= event.MouseInput.Wheel * ZoomSpeed * (CurrentZoom / (MaxZoom * MinZoom));
				break;
			/*case EMIE_LMOUSE_PRESSED_DOWN:
				break;
			case EMIE_RMOUSE_PRESSED_DOWN:
			case EMIE_LMOUSE_LEFT_UP:
			case EMIE_RMOUSE_LEFT_UP:
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
			return;
		
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

		/*if (OldCamera != camera)
		{
			LastCameraTarget = OldTarget = camera->getTarget();
			OldCamera = camera;
		}
		else
		{
			OldTarget += camera->getTarget() - LastCameraTarget;
		}*/


		if (!CursorControl)
		{
			return;
		}
		
		if(!FirstUpdateReceived)
		{
			LastUpdate = Timer->getTime();
			FirstUpdateReceived = true;
		}
		
		u32 TimeDelta = Timer->getTime() - LastUpdate;
		LastUpdate = Timer->getTime();




		// Camera movement
		core::vector3df pos = camera->getPosition();
		core::vector3df target = camera->getTarget();
		core::vector3df translate(0,0,0);
		core::vector3df translate_origin(0,0,0);
		core::vector3df translate2(0,0,0);
		core::vector3df translate3(0,0,0);

		core::vector3df zoom_vector(0,distance*sin(angle),distance*cos(angle));
		core::vector3df zoom_close(0,distance*sin(angle_close),distance*cos(angle_close));

		//core::vector3df zoom_close(0,20,30);
		//core::vector3df zoom_point(0,0,0);
			
		if(isMouseKeyDown(MOUSE_KEY_MIDDLE) && !Zooming) //&& !Translating)
		{
			Dragging = true;

			if(MousePos != MousePos_old)
			{
				core::line3df line = colman->getRayFromScreenCoordinates(MousePos2, camera);
				core::plane3df plane;

				plane.getIntersectionWithLine(line.start, line.getVector(), translate_origin);

				line = colman->getRayFromScreenCoordinates(MousePos2_old, camera);
				plane.getIntersectionWithLine(line.start, line.getVector(), translate2);

				//translate.X += TranslateSpeed*(MousePos.X - MousePos_old.X)*scnmgr->getVideoDriver()->getScreenSize().Width   * (CurrentZoom / (MaxZoom * MinZoom));
				//translate.Z += TranslateSpeed*(MousePos_old.Y - MousePos.Y)*scnmgr->getVideoDriver()->getScreenSize().Height  * (CurrentZoom / (MaxZoom * MinZoom));
			fprintf(stderr, "DEBUG: \n");
				translate.X -= (translate_origin.X - translate2.X);
			fprintf(stderr, "DEBUG: COLL1X %f\n", translate_origin.X);
			fprintf(stderr, "DEBUG: COLL2X %f\n", translate2.X);
			fprintf(stderr, "DEBUG: TRANX %f\n", translate_origin.X - translate2.X);
				translate.Z += (translate2.Z - translate_origin.Z);
			fprintf(stderr, "DEBUG: COLL1Z %f\n", translate_origin.Z);
			fprintf(stderr, "DEBUG: COLL2Z %f\n", translate2.Z);
			fprintf(stderr, "DEBUG: TRANZ %f\n", translate2.Z - translate_origin.Z);
			fprintf(stderr, "DEBUG: COLL1Y %f\n", translate_origin.Z);
			fprintf(stderr, "DEBUG: COLL2Y %f\n", translate2.Z);
			fprintf(stderr, "DEBUG: \n");
				MousePos_old = MousePos;
				MousePos2_old = MousePos2;
			}

			if ((MousePos.X < 0.005) || (MousePos.X > 0.995) || (MousePos.Y < 0.005) || (MousePos.Y > 0.995))
			{
				Scroll_lock = true;
			}
		}
		else
		{
			MousePos_old = MousePos;
			MousePos2_old = MousePos2;
			Dragging = false;
			if((MousePos.X > 0.005) && (MousePos.X < 0.995) && (MousePos.Y > 0.005) && (MousePos.Y < 0.995))
			{
				Scroll_lock = false;
			}
		}
		
		if(CurrentZoom != NewZoom && !Dragging && !Scrolling)
		{
			//(zoom_vector * ((CurrentZoom - MinZoom)/(1.f - MinZoom)) + zoom_close * (1-(CurrentZoom - MinZoom)/(1.f - MinZoom)))*CurrentZoom;

			core::line3df line = colman->getRayFromScreenCoordinates(MousePos2, camera);
			core::plane3df plane;

			plane.getIntersectionWithLine(line.start, line.getVector(), translate3);
				

			const scene::SViewFrustum* f = camera->getViewFrustum();
			
			core::vector3df farLeftUp = f->getFarLeftUp();
			core::vector3df lefttoright = f->getFarRightUp() - farLeftUp;
			core::vector3df uptodown = f->getFarLeftDown() - farLeftUp;


			if(NewZoom >= MaxZoom)
			{
				NewZoom = MaxZoom;
			}
			else if(NewZoom <= MinZoom)
			{
				NewZoom = MinZoom;
			}
			
			
			/*if(CurrentZoom-NewZoom > 0)
			{
			}
			else
			{
				if(CurrentZoom >= 1.f)
				{
					translate.X = -(translate_origin.Z - translate2.Z)*(translate_origin.X - pos.X) * 1.f/CurrentZoom;
					translate.Z = -(translate_origin.Z - translate2.Z)*(translate_origin.Z - pos.Z) * 1.f/CurrentZoom;
				}
			}*/

			//zoom_point.X = -(MousePos.X)*NewZoom;
			//zoom_point.Z = (MousePos.Y)*NewZoom;

			CurrentZoom = NewZoom;
			
		#ifdef _DEBUG
			fprintf(stderr, "DEBUG: CurrentZoom %f\n", CurrentZoom);
		#endif //_DEBUG

			/*if(CurrentZoom < 1.f)
			{
				//zoom_vector += zoom_close * (1.f - CurrentZoom - MinZoom*(CurrentZoom-1.f));

				fprintf(stderr, "DEBUG: MousePos.1 %f\n", ((CurrentZoom - MinZoom)/(1.f - MinZoom)));
				fprintf(stderr, "DEBUG: MousePos.2 %f\n", (1-(CurrentZoom - MinZoom)/(1.f - MinZoom)));
			}
			*/

			Zooming = true;
		}
		else
		{
			NewZoom = CurrentZoom;
			Zooming = false;
		}

		if(!Scroll_lock && !Dragging && !Zooming)
		{
			/*const core::vector3df upVector(camera->getUpVector());*/

			/*core::vector3df tvectX = pos - target;
			tvectX = tvectX.crossProduct(upVector);
			tvectX.normalize();

			const SViewFrustum* const va = camera->getViewFrustum();
			core::vector3df tvectY = (va->getFarLeftDown() - va->getFarRightDown());
			tvectY = tvectY.crossProduct(upVector.Y > 0 ? pos - target : target - pos);
			tvectY.normalize();*/
				
			// get current fps to make camera fps independent 
			//int fps = scnmgr->getVideoDriver()->getFPS();

			//if(fps == 1) fps = 1000; //  Œ—“€À‹

			//fprintf(stderr, "DEBUG: fps %d\n", fps);

			//Mouse Coordinates go from 0 to 1 on both axes

			//fprintf(stderr, "DEBUG: TranslateSpeed %f\n",TranslateSpeed);
			//fprintf(stderr, "DEBUG: 1000/fps %f\n", 3000.f/static_cast<irr::f32>(fps));

			if (MousePos.X < 0.005)   //Up
			{	
				translate.X +=  TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			#ifdef _DEBUG
				fprintf(stderr, "DEBUG: MousePos.X %f\n", MousePos.X);
			#endif //_DEBUG
			}
			else if (MousePos.X > 0.995) //Down
			{
				translate.X -=  TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			#ifdef _DEBUG
				fprintf(stderr, "DEBUG: MousePos.X %f\n", MousePos.X);
			#endif //_DEBUG
			}

			if (MousePos.Y < 0.005)   //Up
			{
				translate.Z -= TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			#ifdef _DEBUG
				fprintf(stderr, "DEBUG: MousePos.Y %f\n", MousePos.Y);
			#endif //_DEBUG
			}
			else if (MousePos.Y > 0.995) //Down
			{
				translate.Z += TranslateSpeed * CurrentZoom * static_cast<irr::f32>(TimeDelta);
			#ifdef _DEBUG
				fprintf(stderr, "DEBUG: MousePos.Y %f\n", MousePos.Y);
			#endif //_DEBUG
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


		target += translate; // + zoom_point;
		pos = target;
		/*pos += translate3 - target;
		pos *= CurrentZoom;*/
		
		/*zoom_vector.X += translate_origin.X - target.X;
		zoom_vector.Y += translate_origin.Y - target.Y;
		zoom_vector.Z += translate_origin.Z - target.Z;*/

		if(CurrentZoom < 1.f)
		{
			pos += (zoom_vector * ((CurrentZoom - MinZoom)/(1.f - MinZoom)) + zoom_close * (1-(CurrentZoom - MinZoom)/(1.f - MinZoom)))*CurrentZoom;
		}
		else
		{
			pos += zoom_vector*CurrentZoom;
		}

		//pos.X += nZoom;

		//pos.rotateXYBy(nRotY, translate);
		//pos.rotateXZBy(-nRotX, translate);

		camera->setPosition(pos);
		camera->setTarget(target);
		//camera->setTarget(translate);
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
