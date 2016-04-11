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
#include <set>
#include <aw/signals/connection.h>
namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {
template<class threading_policy>
struct observer : threading_policy {
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

	/*
	 * TODO: ?
	 */
	observer(observer&& other)
	{
		typename threading_policy::lock_type lock(other);
		connections = std::move(other.connections);
	}

	/*!
	 * Disconnect all signals from this slot
	 */
	void disconnect_all()
	{
		typename threading_policy::lock_type lock(*this);

		for (auto conn : connections)
			conn->disconnect();

		connections.clear();
	}

private:
	friend class observer_access;

	using connection_type = connection<threading_policy>;

	void add(connection_type* conn)
	{
		connections.insert(conn);
	}

	void remove(connection_type* conn)
	{
		connections.erase(conn);
	}

	std::set<connection_type*> connections;
};

template<class threading_policy, class signature>
struct signal;

template<class policy, typename...Args>
struct connection_base;

/*
 * See attorney idiom (or something like that)
 */
class observer_access {
	template<class policy, class signature>
	friend class signal;

	template<class policy, class...Args>
	friend class connection_base;

	template<class policy>
	static void connect(observer<policy>* s, connection<policy>* c)
	{
		s->add(c);
	}

	template<class policy>
	static void disconnect(observer<policy>& s, connection<policy>* c)
	{
		s.remove(c);
	}
};
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_observer_h
