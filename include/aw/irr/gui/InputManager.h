/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_InputManager_impl_
#define _aw_InputManager_impl_
#include <forward_list>

#include <aw/gui/InputManager.h>

namespace irr {
class IrrlichtDevice;
class SEvent;
namespace gui {
class CursorControl;
}
}

namespace aw {
namespace gui {
namespace impl {
class InputManager : public gui::InputManager, public irr::IEventReceiver {
public: //InputManager
	InputManager(irr::IrrlichtDevice* device);
	virtual bool registerReceiver(EventListener* receiver);
	virtual bool unregisterReceiver(EventListener* receiver);

public: //irr::IEventReceiver
	virtual bool OnEvent(const irr::SEvent& event);
private:
	irr::IrrlichtDevice* device;
	irr::gui::ICursorControl* cursor_;
	std::forward_list<EventListener*> receivers_;
	bool convertEvent(const irr::SEvent& irrEvent, Event*& event);
};
} // namespace impl
} // namespace io
} // namespace aw
#endif//_aw_InputManager_impl_
