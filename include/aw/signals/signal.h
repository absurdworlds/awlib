#ifndef aw_signals_signal_h
#define aw_signals_signal_h
#include <set>
#include <map>
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

template<class threading_policy>
struct slot;

template<class signature, class threading_policy>
struct signal;

struct connection {
	virtual ~connection() = default;
	virtual void disconnect() = 0;
};

template<typename...Args>
struct connection_base : connection {
	using signature = void(Args...);

	virtual ~connection_base() = default;
	virtual void operator()(Args...) const = 0;
	virtual slot* target() const = 0;
};

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
	/*!
	 * Destructor is non-virtual, do not store pointers
	 * to derived classes as "slot*".
	 */
	~slot()
	{
		disconnect_all();
	}

	void disconnect_all()
	{
		auto lock = threading_policy::lock();

		for (auto conn : connections)
			conn->disconnect();

		connections.clear();
	}

private:
	friend class slot_access;

	void add(connection* conn)
	{
		auto lock = threading_policy::lock();
		connections.insert(conn);
	}

	void remove(connection* conn)
	{
		auto lock = threading_policy::lock();
		connections.erase(conn);
	}

	std::set<connection*> connections;
};

namespace impl {
template<class T, typename...Args>
struct connection_impl;
}

class slot_access {
	template<class signature, class policy>
	friend class signal;

	template<class T, class...Args, class policy>
	friend class impl::connection_impl;

	template<typename threading_policy>
	static void connect(slot<threading_policy>* s, connection* c)
	{
		s->add(c);
	}

	static void disconnect(slot<threading_policy>* s, connection* c)
	{
		s->remove(c);
	}
};

template<typename...Args, class threading_policy>
struct signal<void(Args...), threading_policy> : threading_policy {
	using signature = void(Args...);

	~signal() = default;

	template<class T>
	connection_ref connect(T& obj, member_func<T,void()> func);

	void disconnect(connection& conn)
	{
		auto lock = impl->lock();
		impl->connections.erase(&conn);
	}

	void disconnect_all()
	{
		auto lock = impl->lock();
		impl->connections.clear();
	}

	void emit(Args...args)
	{
		auto lock = impl->lock();

		for (auto& pair : impl->connections) {
			auto& func = *pair.second;
			func(args...);
		}
	}

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

	// std::map can be quite large (24 - 56 bytes on different implementations)
	// and one class can have several signals, so I'm willing to sacrifice
	// data locality for reduced class size
	struct Data : policy {
		conn_map connections;
	};

	std::unique_ptr<Data> impl{new Data};
};

namespace impl {
template<class T, typename...Args>
struct connection_impl<T,Args...> : connection_base<Args...> {
	using base_type = connection_base<Args...>;

	using signature = typename connection_base<Args...>::signature;

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

	virtual slot* target() const
	{
		return receiver;
	}

private:
	using signal_type = signal<signature>;
	using slot_type   = T;
	using callback_type = member_func<T,signature>;

	friend signal_type;

	connection_impl(signal_type* sender, T* receiver, callback_type func)
		: sender(sender), receiver(receiver), callback(func)
	{ }

	signal_type* sender;
	slot_type* receiver;

	callback_type callback;
};
} // namespace impl

template<typename...Args>
template<class T>
connection_ref signal<void(Args...)>::connect(T& obj, member_func<T,void()> func)
{
	auto conn = new impl::connection_impl<T,Args...>{
		this, &obj, func
	};

	{
		auto lock = impl->lock();
		impl->connections.emplace(conn, connection_ptr(conn));
	}

	slot_access::connect(&obj, conn);

	return {*conn};
}
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_h
