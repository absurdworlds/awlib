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
#include <set>
#include <map>
#include <memory>
#include <aw/utility/static_object.h>
#include <aw/utility/memory/type_pool.h>

#include "memfun.h"
namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {
template<class threading_policy>
struct slot;

template<class signature, class threading_policy>
struct signal;
} // namespace impl;

struct connection {
	virtual ~connection() = default;
	virtual void disconnect() = 0;
};

template<typename...Args>
struct connection_base : connection {
	using signature = void(Args...);

	virtual ~connection_base() = default;
	virtual void operator()(Args...) const = 0;
	//virtual slot* target() const = 0;
};

namespace impl {
template<class threading_policy>
struct slot : threading_policy {
	slot() = default;

	/*!
	 * Destructor is non-virtual, do not store pointers
	 * to derived classes as "slot*".
	 */
	~slot()
	{
		disconnect_all();
	}

	slot(slot const&) = delete;
	slot& operator=(slot const&) = delete;

	/*
	 * TODO: ?
	 */
	slot(slot&& other)
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
	friend class slot_access;

	void add(connection* conn)
	{
		connections.insert(conn);
	}

	void remove(connection* conn)
	{
		typename threading_policy::lock_type lock(*this);

		connections.erase(conn);
	}

	std::set<connection*> connections;
};

template<class policy, class T, typename...Args>
struct connection_impl;

/*
 * See attorney idiom (or something like that)
 */
class slot_access {
	template<class policy, class signature>
	friend class signal;

	template<class policy, class T, class...Args>
	friend class impl::connection_impl;

	template<class policy>
	static void connect(slot<policy>* s, connection* c)
	{
		s->add(c);
	}

	template<class policy>
	static void disconnect(slot<policy>* s, connection* c)
	{
		s->remove(c);
	}
};

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
	connection& connect(T& obj, member_func<T,void()> func);

	/*!
	 * Destroy particular connection
	 */
	void disconnect(connection& conn)
	{
		impl->remove(&conn);
	}

	/*!
	 * Disconnect particular class
	 */
	void disconnect(slot<policy>& s)
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
	using connection_type = connection_base<Args...>;
	using connection_ptr = std::unique_ptr<connection_type>;

	// map<T*, uptr<T>> is used here, as it's easier to
	// use than std::set of unique_ptrs with custom deleter,
	// and uses same amount of space anyway
	// (extra pointer vs pointer to non-empty deleter)
	using conn_map = std::map<connection*, std::unique_ptr<connection_type>>;

public:
	// std::map can be quite large (24 - 56 bytes on different implementations)
	// and one class can have several signals, so I'm willing to sacrifice
	// data locality for reduced class size
	struct signal_impl : policy {
		void insert(connection_type* conn)
		{

			connections.emplace(conn, connection_ptr(conn));
		}

		void remove(connection* conn)
		{
			typename policy::lock_type lock(*this);

			connections.erase(conn);
		}

		conn_map connections;
	};

private:
	std::unique_ptr<signal_impl> impl{new signal_impl};
};

template<class S, class T, typename...Args>
struct connection_impl : connection_base<Args...> {
	using base_type = connection_base<Args...>;

	using signature = typename connection_base<Args...>::signature;

	using signal_type = typename S::signal_impl;
	using slot_type   = T;
	using callback_type = member_func<T,signature>;

	virtual ~connection_impl()
	{
		sender = nullptr;
		if (receiver)
			slot_access::disconnect(receiver, this);
	}

	virtual void disconnect()
	{
		if (sender)
			sender->remove(this);
	}

	virtual void operator()(Args... args) const
	{
		(receiver->*callback)(args...);
	}

	virtual slot_type* target() const
	{
		return receiver;
	}

private:
	friend S;

	connection_impl(signal_type* sender, T* receiver, callback_type func)
		: sender(sender), receiver(receiver), callback(func)
	{ }

	signal_type* sender;
	slot_type* receiver;

	callback_type callback;

public:
	void* operator new(size_t count)
	{
		constexpr size_t size = sizeof(connection_impl);
		auto& p = static_object<pool>::instance();
		return p.alloc();
	}

	void operator delete(void* ptr)
	{
		constexpr size_t size = sizeof(connection_impl);
		auto& p = static_object<pool>::instance();
		p.dealloc(ptr);
	}

private:
	struct pool : memory::growing_pool<sizeof(connection_impl)> {
		using base = memory::growing_pool<sizeof(connection_impl)>;
		pool()
			: base(4096)
		{}
	};
};

template<class P, typename...Args>
template<class T>
connection& signal<P,void(Args...)>::connect(T& obj, member_func<T,void()> func)
{
	auto conn = new impl::connection_impl<signal,T,Args...>{
		impl.get(), &obj, func
	};

	typename P::lock_n_type lock(*impl, obj);

	impl->insert(conn);

	slot_access::connect(&obj, conn);

	return *conn;
}
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_h
