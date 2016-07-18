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
#include <map>
#include <memory>
#include <aw/signals/connection.h>
namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {
template<class threading_policy>
struct signal_base;

template<class policy>
struct signal_impl : policy {
	using connection_type = connection<policy>;
	using connection_ptr = std::unique_ptr<connection_type>;

	signal_impl(signal_base<policy>* parent)
		: parent(parent)
	{}

	// map<T*, uptr<T>> is used here, as it's easier to
	// use than std::set of unique_ptrs with custom deleter,
	// and uses same amount of space anyway
	// (extra pointer vs pointer to non-empty deleter)
	using conn_map = std::map<connection_type*, connection_ptr>;

	void insert(connection_type* conn)
	{
		connections.emplace(conn, connection_ptr(conn));
	}

	void remove(connection_type* conn)
	{
		connections.erase(conn);
	}

	// signal_impl exists only to reduce signal's size
	// std::map can be quite large (24 - 56 bytes on different implementations)
	// and one class can have several signals, so I'm willing to sacrifice
	// data locality for reduced class size
	conn_map connections;
	signal_base<policy>* parent;
};

template<class policy>
struct signal_base {
	using signal_imp = signal_impl<policy>;

	signal_base() = default;
	~signal_base() = default;

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
	 * Move \a other signal into this signal.
	 * Other signal becomes empty, as though it
	 * was default-constructed.
	 */
	signal_base(signal_base&& other)
	{
		typename policy::lock_type lock(*other.impl);

		impl.swap(other.impl);
		impl->parent = this;
	}

	/*!
	 * Move \a other signal into this signal.
	 * Other signal becomes empty, as though it
	 * was default-constructed.
	 */
	signal_base& operator=(signal_base&& other)
	{
		/*
		 * This code is supposed to safely swap impls.
		 *
		 * Because attempt to destruct a locked mutex
		 * results in undefined behavior, I can't release
		 * impl while it's locked.
		 */
		/*
		 * Another thought:
		 * will this cause problems?
		 * thread1: sig1 = std::move(sig2);
		 * thread1: { ...
		 * thread1:     impl.swap(temp);
		 *
		 * threadA: sig1.connect(...); // attempts to lock temp
		 *
		 * thread1: releases lock
		 *
		 * threadB: sig2.connect(...); // locks temp
		 *
		 * threadA: still waiting on temp
		 */
		auto temp = std::make_unique<signal_impl<policy>>();

		typename policy::lock_type lock2(*temp);

		{
			typename policy::lock_n_type lock(*impl, *other.impl);

			impl.swap(temp);
			impl.swap(other.impl);
			impl->parent = this;
		}
	}

	/*!
	 * Destroy particular connection
	 */
	void disconnect(connection<policy>& conn)
	{
		typename policy::lock_type lock(*impl);
		impl->remove(&conn);
	}

	/*!
	 * Disconnect particular class
	 */
	void disconnect(observer<policy>& s)
	{
		typename policy::lock_type lock(*impl);

		auto iter = std::begin(impl->connections);
		auto end  = std::end(impl->connections);
		while (iter != end) {
			auto* target = iter->second->target();
			if (&target == &s) {
				impl->connections.erase(iter++);
			} else {
				++iter;
			}
		}
	}

	/*!
	 * Destroy all connections
	 */
	void disconnect_all()
	{
		typename policy::lock_type lock(*impl);
		impl->connections.clear();
	}

protected:
	// std::map can be quite large (24 - 56 bytes on different implementations)
	// and one class can have several signals, so I'm willing to sacrifice
	// data locality for reduced class size
	std::unique_ptr<signal_impl<policy>> impl{new signal_impl<policy>{this}};
};

} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_base_h
