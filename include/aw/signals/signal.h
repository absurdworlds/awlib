#ifndef aw_signals_signal_h
#define aw_signals_signal_h
#include <set>
#include <functional>
#include <memory>
#include <mutex>

#include "memfun.h"
namespace aw {
inline namespace signals {
struct single_threaded {
	struct lock_dummy {};
	struct mutex_dummy {};

	using lock_type = lock_dummy;

	lock_type lock()
	{
		return lock_dummy{};
	}
};

struct multi_threaded {
	using lock_type = std::unique_lock<std::mutex>;

	lock_type lock()
	{
		return lock_type(mtx);
	}

	std::mutex mtx;
};

using default_policy = single_threaded;


template<class threading_policy = default_policy>
struct slot;

template<class signature, class threading_policy = default_policy>
struct signal;

struct connection {
	virtual void disconnect() = 0;

private:
	template<class threading_policy>
	friend class aw::slot;

	template<class signature, class threading_policy>
	friend class aw::signal;

	virtual void notify_signal() = 0;
	virtual void notify_slot()   = 0;
};

namespace impl {
/*
 * Helper to automatically notify signals/slots
 * that connectionwas erased.
 * Not the nicest solution, but all other solutions
 * weren't nice either.
 */
template<class T, class F>
struct holder {
	holder(T* ptr, bool do_call = false)
		: ptr(ptr), do_call(do_call)
	{}

	~holder()
	{
		if (do_call)
			F{}(ptr);
	}

	holder(holder const&) = delete;
	holder& operator=(holder const&) = delete;

	holder(holder&& other)
		: ptr(other.ptr), do_call(other.do_call)
	{
		other.do_call = false;
	}

	holder& operator=(holder&& other)
	{
		ptr = other.ptr;
		do_call = other.do_call;
		other.do_call = false;
	}

	T* operator->()
	{
		return ptr;
	}

	T* ptr;
	bool do_call;
};

template<class T, class F, class E>
bool operator<(holder<T,F> const& a, holder<T,E> const& b)
{
	return a.ptr < b.ptr;
}

template<class Signature>
struct connection_base;

template<typename...Args>
struct connection_base<void(Args...)> : connection {
	virtual void operator()(Args...) const = 0;
	
	using signature = void(Args...);
};

template<typename S, typename T, typename... Args>
connection_base<void(Args...)>*
make_connection(S* signal, T* slot, member_func<T,void(Args...)> callback);

template<class S, class T, class Signature>
struct connection_impl;
} // namespace impl

/*!
 * Wrapper around pointer to connection.
 */
/*
 * Could've used reference_wrapper, but it needs to be empty.
 * Could've used plain reference, but then user needs to take ptr
 * And I don't want
 */
struct connection_ref {
	connection_ref() = default;
	~connection_ref() = default;
	connection_ref(connection_ref const&) = default;
	connection_ref& operator=(connection_ref const&) = default;

	connection_ref(connection& conn)
		: conn(&conn)
	{}

	void disconnect()
	{
		conn->disconnect();
	}

private:
	connection* conn = nullptr;
};

template<class threading_policy>
struct slot : threading_policy {
	~slot()
	{
		disconnect_all();
	}

	void disconnect_all()
	{
		auto lock = threading_policy::lock();
		connections.clear();
	}

private:
	template<class S, class T, class signature> friend class impl::connection_impl;
	template<class signature, class policy> friend class signal;

	void regcon(connection* conn)
	{
		auto lock = threading_policy::lock();
		connections.emplace(conn, true);
	}

	void remove(connection* conn)
	{
		auto lock = threading_policy::lock();
		connections.erase(conn);
	}

	struct on_destruct {
		void operator()(connection* conn)
		{
			conn->notify_signal();
		}
	};

	using connection_holder = impl::holder<connection, on_destruct>;

	std::set<connection_holder> connections;

};

template<typename...Args, class threading_policy>
struct signal<void(Args...), threading_policy> : threading_policy {
	using signature = void(Args...);

	~signal()
	{
		disconnect_all();
	}

	void disconnect_all()
	{
		auto lock = threading_policy::lock();
		connections.clear();
	}

	/*
	template<class T>
	connection_ref connect(T* obj, member_func<T,void()> func)
	{
		auto conn = make_connection(this, obj, func);
		return {*conn};
	}
	*/

	template<class T>
	connection_ref connect(T& obj, member_func<T,void()> func)
	{
		auto conn = impl::make_connection(this, &obj, func);
		return {*conn};
		//return connect(&obj, func);
	}

	void emit(Args...args)
	{
		auto lock = threading_policy::lock();

		for (auto& conn : connections) {
			// Guaranteed to be of connection_type, because
			// values are inserted only in connect() method,
			// which emplaces value of connection_type into
			// set
			auto& ref = *static_cast<connection_type const*>(conn.ptr);
			ref(args...);
		}
	}

	void operator()(Args...args)
	{
		emit(args...);
	}

private:
	template<class S, class T, class signature> friend class impl::connection_impl;

	using connection_type = impl::connection_base<signature>;

	void regcon(connection* conn)
	{
		auto lock = threading_policy::lock();
		connections.emplace(conn, true);
	}

	void remove(connection* conn)
	{
		auto lock = threading_policy::lock();
		connections.erase(conn);
	}

	struct on_destruct {
		void operator()(connection* conn)
		{
			conn->notify_slot();
		}
	};

	using connection_holder = impl::holder<connection, on_destruct>;
	std::set<connection_holder> connections;
};

namespace impl {
template<class S, class T, typename...Args>
struct connection_impl<S,T,void(Args...)> : connection_base<void(Args...)> {
	virtual void disconnect()
	{
		if (sender)
			sender->remove(this);
	}

	virtual void operator()(Args... args) const
	{
		(receiver->*callback)(args...);
	}

	using signature = typename connection_base<void(Args...)>::signature;

private:
	using signal_type = S;
	using slot_type   = T;
	using callback_type = member_func<T,signature>;
	using base_type = connection_base<void(Args...)>;

	friend base_type* make_connection<S,T,Args...>(S*, T*, callback_type);

	connection_impl(S* sender, T* receiver, callback_type func)
		: sender(sender), receiver(receiver), callback(func)
	{
		sender->regcon(this);
		receiver->regcon(this);
	}

	virtual void notify_signal()
	{
		if (sender) {
			receiver = nullptr;
			sender->remove(this);
			delete this;
		}
	}

	virtual void notify_slot()
	{
		if (receiver) {
			sender = nullptr;
			receiver->remove(this);
			delete this;
		}
	}

	signal_type* sender;
	slot_type* receiver;

	callback_type callback;
};

template<typename S, typename T, typename... Args>
connection_base<void(Args...)>*
make_connection(S* signal, T* slot, member_func<T,void(Args...)> callback)
{
	return new connection_impl<S,T,void(Args...)>(signal, slot, callback);
}
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_h
