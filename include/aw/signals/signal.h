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
#include <aw/signals/signal_base.h>
#include <aw/signals/connection_impl.h>
namespace aw {
namespace signals {
inline namespace v1 {
namespace impl {
template<class policy, typename signature>
struct signal;

template<class policy, typename...Args>
class signal<policy, void(Args...)> : signal_base<policy> {
	using base_type = signal_base<policy>;
	using base_type::impl;
public:
	using signature = void(Args...);
	using connection_type = connection_impl<policy, Args...>;

	signal() = default;
	~signal() = default;

	signal(signal&& other) = default;

	static connection_type& conn_cast(connection<policy>* conn)
	{
		return *static_cast<connection_type*>(conn);
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
		for (auto& pair : impl->connections) {
			auto conn = conn_cast(pair.first);
			temp->impl->insert(conn.clone(temp));
		}
		return temp;
	}

	/*!
	 * Add member function to list of observers.
	 * Each time signal is called, it will call each of callbacks.
	 */
	template<class T>
	connection<policy>& connect(T& obj, mem_fn<void(T*,Args...)> func)
	{
		auto conn = new connection_type{impl.get(), obj, func};

		typename policy::lock_n_type lock(*impl, obj);

		impl->insert(conn);

		observer_access::connect(&obj, conn);

		return *conn;
	}

	/*!
	 * Emitting signal causes it to call each of connected
	 * slots.
	 */
	void emit(Args...args)
	{
		typename policy::lock_type lock(*impl);

		for (auto& pair : impl->connections) {
			auto& func = conn_cast(pair.first);
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
};
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_h
