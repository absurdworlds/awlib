/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIEvent_
#define _aw_GUIEvent_
#include <aw/common/types.h>
#include <aw/common/Event.h>
#include <aw/gui/Element.h>
namespace aw {
namespace gui {

struct GUIEvent : public EventId<GUIEvent>{
public:
	enum Action {
		Unknown,
		Closed,
		Hovered,
		Left,
		Focused,
		Unfocused,
		FocusLost = Unfocused,
	};

	Action action;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUIEvent_
