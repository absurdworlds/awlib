/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_connection_impl_h
#define aw_signals_connection_impl_h
#include <aw/types/support/reinterpret.h>
#include <aw/utility/static_object.h>
#include <aw/utility/memory/growing_pool.h>
#include <aw/signals/observer.h>
namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {
template<class threading_policy, class signature>
struct signal;

template<class T, class sig>
struct memfun;

template<class T, typename R, typename...Args>
struct memfun<T, R(Args...)> {
	using type = R (T::*)(Args...);
};

template<class T, class sig>
using member_func = typename memfun<T,sig>::type;

class _unknown;
template<typename R, typename... Args>
using unknown_mem_fn = R(_unknown::*)(Args...);

template<class polcy, class signature>
struct func;

template<class policy, typename...Args>
struct func<policy, void(Args...)> {
	using storage = typename std::aligned_storage<
	        sizeof(unknown_mem_fn<void,Args...>),
	        alignof(unknown_mem_fn<void,Args...>)
	>::type;

	template<class T> static
	void invoke(storage const& data, observer<policy>* obj, Args... args)
	{
		auto func = reinterpret_any<member_func<T,void(Args...)>>(data);
		T* ptr = static_cast<T*>(obj);
		(ptr->*func)(args...);
	}
};

template<class policy, typename...Args>
struct connection_base : connection<policy> {
	using signature = void(Args...);

	using signal_type   = signal<policy,signature>;
	using signal_impl   = typename signal_type::signal_impl;

	using storage_type = typename func<policy,void(Args...)>::storage;
	using invoker_type = void(*)(storage_type const&, observer<policy>*, Args...);

	~connection_base()
	{
		auto& receiver = connection<policy>::target();
		{
			typename policy::lock_type lock(receiver);
			observer_access::disconnect(receiver, this);
		}
	}

	virtual void disconnect();

	void operator()(Args... args) const
	{
		auto& receiver = connection<policy>::target();
		invoke(storage, &receiver, args...);
	}

	void* operator new(size_t count);
	void operator delete(void* ptr);

private:
	friend signal_type;

	template<typename T>
	connection_base(signal_impl* sender, T& obj, member_func<T,signature> fn)
		: connection<policy>(obj), sender(sender)
	{
		invoke  = func<policy,void(Args...)>::template invoke<T>;
		storage = reinterpret_any<storage_type>(fn);
	}

	signal_impl* sender;

	storage_type storage;
	invoker_type invoke;

};

template<class policy, size_t size>
struct connection_pool : policy, memory::growing_pool<size> {
	using base = memory::growing_pool<size>;
	connection_pool() : base(4096) { }

	void* alloc()
	{
		typename policy::lock_type lock(*this);
		return base::alloc();
	}

	void dealloc(void* ptr)
	{
		typename policy::lock_type lock(*this);
		return base::dealloc(ptr);
	}
};

template<class policy, typename... Args>
void* connection_base<policy,Args...>::operator new(size_t count)
{
	constexpr size_t size = sizeof(connection_base);
	using conn_pool = static_object<connection_pool<policy,size>>;
	static auto& p = conn_pool::instance();
	return p.alloc();
}

template<class policy, typename... Args>
void connection_base<policy,Args...>::operator delete(void* ptr)
{
	constexpr size_t size = sizeof(connection_base);
	using conn_pool = static_object<connection_pool<policy,size>>;
	static auto& p = conn_pool::instance();
	p.dealloc(ptr);
}
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_connection_impl_h
