/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_connection_h
#define aw_signals_connection_h
#include <aw/types/mem_fn.h>
#include <aw/types/support/reinterpret.h>
#include <aw/utility/static_object.h>
#include <aw/utility/memory/pool.h>
namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {
template<class threading_policy>
struct observer;

template<class threading_policy>
struct signal_impl;

template<class threading_policy>
struct signal_base;

template<class policy, class signature>
struct signal;

template<class policy>
struct connection {
	using signal_type   = signal_base<policy>;
	using signal_i_type = signal_impl<policy>;
	using observer_type = observer<policy>;

	~connection();
	void disconnect();

	signal_type& source() const;

	observer_type& target() const
	{
		return *receiver;
	}

	template<typename... Args>
	void invoke(Args&&...args)
	{
		auto inv = Invoker<Args...>::cast(invoker);
		inv(storage, receiver, std::forward<Args>(args)...);
	}

	using unknown_mem_fn = mem_fn<void(_unknown*)>;

	using storage_type = typename std::aligned_storage<
		sizeof(unknown_mem_fn),
		alignof(unknown_mem_fn)
	>::type;


	template<typename...Args>
	struct Invoker {
		using invoker_type = void(storage_type const&, observer<policy>*, Args...);

		static invoker_type* cast(void* invoker)
		{
			return reinterpret_cast<invoker_type*>(invoker);
		}

		template<class T> static
		void invoke(storage_type const& data, observer<policy>* obj, Args... args)
		{
			auto func = reinterpret_any<mem_fn<void(T*,Args...)>>(data);
			T* ptr = static_cast<T*>(obj);
			(ptr->*func)(args...);
		}
	};

	void* operator new(size_t count);
	void operator delete(void* ptr);

protected:
	template<class P, typename S>
	friend class signal;

	template<typename T, typename...Args>
	connection(signal_i_type& sig, T& obj, mem_fn<void(T*,Args...)> fn)
		: sender(&sig), receiver(&obj)
	{
		invoker = (void*)Invoker<Args...>::template invoke<T>;
		storage = reinterpret_any<storage_type>(fn);
	}

	connection(signal_i_type& impl, connection& other)
	        : sender(&impl), receiver(other.receiver), invoker(other.invoker),
		  storage_type(other.storage)
	{ }

	connection* clone(signal_i_type& temp) const
	{
		return new connection{temp, *this};
	}

private:
	signal_i_type* sender;
	observer_type* receiver;

	void* invoker;
	storage_type storage;

};

template<class policy>
struct connection_pool : policy, memory::specific_pool<connection<policy>> {
	using base = memory::specific_pool<connection<policy>>;
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

template<class policy>
void* connection<policy>::operator new(size_t count)
{
	using pool_type = connection_pool<policy>;
	using conn_pool = static_object<pool_type>;
	static auto& p = conn_pool::instance();
	return p.alloc();
}

template<class policy>
void connection<policy>::operator delete(void* ptr)
{
	using pool_type = connection_pool<policy>;
	using conn_pool = static_object<pool_type>;
	static auto& p = conn_pool::instance();
	p.dealloc(ptr);
}
} // namespace impl
} // namespace v1
} // namespace signals
} // namespace aw
#endif//aw_signals_connection_h
