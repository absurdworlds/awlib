/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_observer_h
#define aw_signals_observer_h
#include <vector>
#include <algorithm>
#include <aw/signals/v2/signal_base.h>
namespace aw {
namespace signals {
inline namespace v2 {
class observer;
class signal_base;

struct signal_access {
	friend observer;

	static void on_disconnect(signal_base& sig, observer& obs)
	{
		sig.on_disconnect(obs);
	}
};

/*!
 * Observers can be connected to signals to be notified
 * every time the signal is emitted.
 * Observer automatically disconnects itself on destruction.
 */
struct observer {
	observer() = default;

	/*!
	 * Destructor is non-virtual, do not store pointers
	 * to derived classes as "observer*".
	 */
	~observer()
	{
		disconnect_all();
	}

	observer(observer const&) = delete;
	observer& operator=(observer const&) = delete;

	/*!
	 * Disconnect particular signal
	 */
	void disconnect(signal_base& sig)
	{
		auto begin = remove(sig);

		for (auto iter = begin; iter != end(connections); ++iter)
			signal_access::on_disconnect(**iter, *this);

		if (begin != end(connections))
			connections.erase(begin, end(connections));
	}

	/*!
	 * Disconnect all signals from this slot
	 */
	void disconnect_all()
	{
		for (auto signal : connections)
			signal_access::on_disconnect(*signal, *this);

		connections.clear();
	}

private:
	friend class observer_access;


	std::vector<signal_base*> connections;

	auto remove(signal_base& sig) -> decltype(connections.begin())
	{
		auto begin = std::begin(connections);
		auto end   = std::end(connections);

		return std::remove(begin, end, &sig);
	}
};

void observer_access::connect(observer& obs, signal_base& sig)
{
	obs.connections.push_back(&sig);
}

void observer_access::on_disconnect(observer& obs, signal_base& sig)
{
	auto begin = obs.remove(sig);

	auto end = std::end(obs.connections);
	if (begin != end)
		obs.connections.erase(begin, end);
}
} // namespace v2
} // namespace signals
} // namespace aw
#endif//aw_signals_observer_h
