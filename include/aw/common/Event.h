/*
 * Copyright (C) 2015  hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_common_Event_
#define _aw_common_Event_
#include <aw/common/types.h>
namespace aw {
class Event {
public:
	virtual bool is(size_t id) = 0;
	virtual size_t getType() = 0;
protected:
	static size_t eventTypes;
};

template <class Derived>
class EventId : public Event {
public:
	static size_t type() {
		static size_t id = eventTypes++;
		return id;
	}

	virtual bool is(size_t id)
	{
		return type() == id;
	}

	virtual size_t getType() {
		return type();
	}
protected:
	EventId<Derived>()
	{
	}
};

template <class E>
E* event_cast(Event* event) {
	if (event->is(E::type()))
		return static_cast<E*>(event);

	return nullptr;
}
} // namespace aw
#endif //_aw_common_Event_
