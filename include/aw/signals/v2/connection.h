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
namespace aw {
namespace signals {
inline namespace v2 {
// Forward declaration of observer;
class observer;

struct connection {
	template<typename T, typename...Args>
	connection(T& obj, mem_fn<void(T*,Args...)> fn)
		: receiver(&obj)
	{
		invoker = (void*)Invoker<Args...>::template invoke<T>;
		storage = reinterpret_any<storage_type>(fn);
	}

	connection(connection const& other)
	        : receiver(other.receiver),
		  invoker(other.invoker), storage(other.storage)
	{ }

	observer& target() const
	{
		return *receiver;
	}

private:
	friend class connection_invoker;
	using unknown_mem_fn = mem_fn<void(_unknown*)>;

	using storage_type = typename std::aligned_storage<
		sizeof(unknown_mem_fn),
		alignof(unknown_mem_fn)
	>::type;

	template<typename...Args>
	struct Invoker {
		using invoker_type = void(storage_type const&, observer*, Args...);

		static invoker_type* cast(void* invoker)
		{
			return reinterpret_cast<invoker_type*>(invoker);
		}

		template<class T> static
		void invoke(storage_type const& data, observer* obj, Args... args)
		{
			auto func = reinterpret_any<mem_fn<void(T*,Args...)>>(data);
			T* ptr = static_cast<T*>(obj);
			(ptr->*func)(args...);
		}
	};

	template<typename... Args>
	void invoke(Args&&...args)
	{
		auto invoker = Invoker<Args...>::cast(this->invoker);
		invoker(storage, receiver, std::forward<Args>(args)...);
	}

	observer* receiver;

	void* invoker;
	storage_type storage;
};

class connection_invoker {
	template<class signature>
	friend class signal;

	template<typename... Args> static
	void invoke(connection& conn, Args&&...args)
	{
		conn.invoke(std::forward<Args>(args)...);
	}
};
} // namespace v2
} // namespace signals
} // namespace aw
#endif//aw_signals_connection_h
