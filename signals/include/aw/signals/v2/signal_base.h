/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_signal_base_h
#define aw_signals_signal_base_h
#include <vector>
#include <algorithm>
#include <aw/signals/v2/connection.h>
namespace aw {
namespace signals {
inline namespace v2 {
// Forward declaration of signal_base for observer_access
class signal_base;

/*!
 * Ensures that only connection can add and remove itself
 * to/from observer.
 *
 * See attorney idiom.
 */
class observer_access {
	friend class signal_base;

	template<class signature>
	friend class signal;

	static void connect(observer& obs, signal_base& sig);
	static void on_disconnect(observer& obs, signal_base& sig);
};

struct signal_impl {
	void insert(connection conn)
	{
		connections.push_back(conn);
	}

	auto remove(observer& obs)
	{
		auto begin = std::begin(connections);
		auto end   = std::end(connections);

		auto pred  = [&obs] (connection& conn) {
			return &conn.target() == &obs;
		};

		return std::remove_if(begin, end, pred);
	}

	std::vector<connection> connections;
};

struct signal_base {
	signal_base() = default;
	~signal_base()
	{
		disconnect_all();
	}

	/*!
	 * To copy a signal use clone()
	 *
	 * I see only two reasonable behaviours when copying an object
	 * with signals:
	 * A. Copy the object, default-initialize signals
	 * B. Copy the object, and connect signals to same slots
	 *    that originals were connected to.
	 */
	signal_base(signal_base const&) = delete;
	signal_base& operator=(signal_base const&) = delete;

	/*!
	 * Disconnect particular class
	 */
	void disconnect(observer& obs)
	{
		auto begin = impl->remove(obs);

		for (auto iter = begin; iter != end(impl->connections); ++iter)
			observer_access::on_disconnect(iter->target(), *this);

		if (begin != end(impl->connections))
			impl->connections.erase(begin, end(impl->connections));
	}

	/*!
	 * Destroy all connections
	 */
	void disconnect_all()
	{
		for (auto conn : impl->connections)
			observer_access::on_disconnect(conn.target(), *this);

		impl->connections.clear();
	}

protected:
	friend class signal_access;

	void on_disconnect(observer& obs)
	{
		auto begin = impl->remove(obs);

		if (begin != end(impl->connections))
			impl->connections.erase(begin, end(impl->connections));
	}

	std::unique_ptr<signal_impl> impl{new signal_impl};
};
} // namespace 2
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_base_h
