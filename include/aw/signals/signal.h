/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_signal_h
#define aw_signals_signal_h
#include <map>
#include <memory>
#include <aw/signals/connection_impl.h>

namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {

template<class policy, typename...Args>
struct signal<policy, void(Args...)> {
	using signature = void(Args...);

	signal() = default;
	~signal() = default;

	/*!
	 * To copy a signal use clone()
	 *
	 * I see only two reasonable behaviours when copying an object
	 * with signals:
	 * A. Copy the object, default-initialize signals
	 * B. Copy the object, and connect signals to same slots
	 *    that originals were connected to.
	 */
	signal(signal const&) = delete;
	signal& operator=(signal const&) = delete;


	/*!
	 * Move \a other signal into this signal.
	 * Other signal becomes empty, as though it
	 * was default-constructed.
	 */
	signal(signal&& other)
	{
		typename policy::lock_type lock(*other.impl);

		impl.swap(other.impl);
	}

	/*!
	 * Move \a other signal into this signal.
	 * Other signal becomes empty, as though it
	 * was default-constructed.
	 */
	signal& operator=(signal&& other)
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
		auto temp = std::make_unique<signal_impl>();

		typename policy::lock_type lock2(*temp);

		{
			typename policy::lock_n_type lock(*impl, *other.impl);

			impl.swap(temp);
			impl.swap(other.impl);
		}
	}

	/*!
	 * Clone a signal.
	 * Creates a signal and connects it to each slot
	 * this signal is connected to.
	 */
	signal clone() const
	{
		typename policy::lock_type lock(*impl);

		signal temp;
		for (auto& conn : impl->connections)
			temp.connect(*conn.receiver, conn.callback);
		return temp;
	}

	/*!
	 * Add member function to list of observers.
	 * Each time signal is called, it will call each of callbacks.
	 */
	template<class T>
	connection<policy>& connect(T& obj, member_func<T,void()> func)
	{
		auto conn = new impl::connection_base<policy,Args...>{
			impl.get(), obj, func
		};

		typename policy::lock_n_type lock(*impl, obj);

		impl->insert(conn);

		observer_access::connect(&obj, conn);

		return *conn;
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
			if (iter->second->target() == &s) {
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

	/*!
	 * Emitting signal causes it to call each of connected
	 * slots.
	 */
	void emit(Args...args)
	{
		typename policy::lock_type lock(*impl);

		for (auto& pair : impl->connections) {
			auto& func = *pair.second;
			func(args...);
		}
	}

	/*!
	 * Emit signal.
	 * \see emit
	 */
	void operator()(Args...args)
	{
		emit(args...);
	}

private:
	using key_type = connection<policy>*;
	using connection_type = connection_base<policy, Args...>;
	using connection_ptr = std::unique_ptr<connection_type>;

	// map<T*, uptr<T>> is used here, as it's easier to
	// use than std::set of unique_ptrs with custom deleter,
	// and uses same amount of space anyway
	// (extra pointer vs pointer to non-empty deleter)
	using conn_map = std::map<key_type, std::unique_ptr<connection_type>>;

public:
	// std::map can be quite large (24 - 56 bytes on different implementations)
	// and one class can have several signals, so I'm willing to sacrifice
	// data locality for reduced class size
	struct signal_impl : policy {
		void insert(connection_type* conn)
		{
			connections.emplace(conn, connection_ptr(conn));
		}

		void remove(connection<policy>* conn)
		{
			connections.erase(conn);
		}

		conn_map connections;
	};

private:
	std::unique_ptr<signal_impl> impl{new signal_impl};
};

template<class policy, typename... Args>
void connection_base<policy,Args...>::disconnect()
{
	typename policy::lock_type lock(*sender);
	sender->remove(this);
}
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_h
