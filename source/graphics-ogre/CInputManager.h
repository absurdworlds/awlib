/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CInputManager_
#define _hrengin_CInputManager_

#include <array>
#include <forward_list>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <hrengin/core/ISettingsManager.h>

#include <hrengin/gui/IInputManager.h>

namespace hrengin {
namespace gui {

/*
	Class for handling user input. It inherits from irr::IEventReceiver
	so it can be passed into Irrlicht device as an user event receiver.
	Then it handles events through OnEvent() callback.

	To access user input, use IGUIManager::getInputManager()
 */
class CInputManager : public IInputManager, public OIS::KeyListener, public OIS::MouseListener {
public: //IInputManager
	CInputManager(core::ISettingsManager* settings);
	virtual bool registerReceiver(IUserInputReceiver* receiver);
	virtual bool unregisterReceiver(IUserInputReceiver* receiver);

	// OIS::KeyListener
	virtual InputEvent key(OIS::KeyEvent const& arg);
	virtual bool keyPressed( OIS::KeyEvent const& arg );
	virtual bool keyReleased( OIS::KeyEvent const& arg );
	// OIS::MouseListener
	virtual InputEvent mouse(OIS::MouseEvent const& arg);
	virtual bool mouseMoved( OIS::MouseEvent const& arg );
	virtual bool mousePressed(  OIS::MouseEvent const& arg, OIS::MouseButtonID id );
	virtual bool mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id );

	virtual void broadcast(InputEvent event);
private:
	OIS::InputManager* inputMgr_;
	OIS::Mouse*    cursor_;
	OIS::Keyboard* keyboard_;
	std::forward_list<IUserInputReceiver*> receivers_;

	std::array<KeyCode,0xFF> keyMap_;

	void genKeyMap()
	{
		keyMap_.fill(KeyCode(0xFF));

		keyMap_[OIS::KC_0] = KEY_KEY_0;
		keyMap_[OIS::KC_1] = KEY_KEY_1;
		keyMap_[OIS::KC_2] = KEY_KEY_2;
		keyMap_[OIS::KC_3] = KEY_KEY_3;
		keyMap_[OIS::KC_4] = KEY_KEY_4;
		keyMap_[OIS::KC_5] = KEY_KEY_5;
		keyMap_[OIS::KC_6] = KEY_KEY_6;
		keyMap_[OIS::KC_7] = KEY_KEY_7;
		keyMap_[OIS::KC_8] = KEY_KEY_8;
		keyMap_[OIS::KC_9] = KEY_KEY_9;
		keyMap_[OIS::KC_0] = KEY_KEY_0;

		keyMap_[OIS::KC_A] = KEY_KEY_A;
		keyMap_[OIS::KC_B] = KEY_KEY_B;
		keyMap_[OIS::KC_C] = KEY_KEY_C;
		keyMap_[OIS::KC_D] = KEY_KEY_D;
		keyMap_[OIS::KC_E] = KEY_KEY_E;
		keyMap_[OIS::KC_F] = KEY_KEY_F;
		keyMap_[OIS::KC_G] = KEY_KEY_G;
		keyMap_[OIS::KC_H] = KEY_KEY_H;
		keyMap_[OIS::KC_I] = KEY_KEY_I;
		keyMap_[OIS::KC_J] = KEY_KEY_J;
		keyMap_[OIS::KC_K] = KEY_KEY_K;
		keyMap_[OIS::KC_L] = KEY_KEY_L;
		keyMap_[OIS::KC_M] = KEY_KEY_M;
		keyMap_[OIS::KC_N] = KEY_KEY_N;
		keyMap_[OIS::KC_O] = KEY_KEY_O;
		keyMap_[OIS::KC_P] = KEY_KEY_P;
		keyMap_[OIS::KC_Q] = KEY_KEY_Q;
		keyMap_[OIS::KC_R] = KEY_KEY_R;
		keyMap_[OIS::KC_S] = KEY_KEY_S;
		keyMap_[OIS::KC_T] = KEY_KEY_T;
		keyMap_[OIS::KC_U] = KEY_KEY_U;
		keyMap_[OIS::KC_V] = KEY_KEY_V;
		keyMap_[OIS::KC_W] = KEY_KEY_W;
		keyMap_[OIS::KC_X] = KEY_KEY_X;
		keyMap_[OIS::KC_Y] = KEY_KEY_Y;
		keyMap_[OIS::KC_Z] = KEY_KEY_Z;
	}
};


} // namespace io
} // namespace hrengin

#endif//_hrengin_CInputManager_
