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
#include <aw/signals/v2/signal_base.h>
#include <aw/signals/v2/observer.h>
namespace aw {
namespace signals {
inline namespace v2 {
template<typename signature>
class signal;

template<typename...Args>
class signal<void(Args...)> : signal_base {
	using base_type = signal_base;
	using base_type::impl;
public:
	using signature = void(Args...);

	signal() = default;
	~signal() = default;

	/*!
	 * Clone a signal.
	 * Creates a signal with same set of connections as this one.
	 */
	signal clone() const
	{
		signal temp;
		temp.impl->connections = impl->connections;
		return temp;
	}

	/*!
	 * Add member function to list of observers.
	 * Each time signal is called, it will call each of callbacks.
	 */
	template<class T>
	void connect(T& obj, mem_fn<void(T*,Args...)> fn)
	{
		observer_access::connect(obj, *this);
		impl->connections.emplace_back(obj, fn);
	}

	/*!
	 * Emitting signal causes it to call each of connected slots.
	 */
	void emit(Args&&...args)
	{
		for (auto& conn : impl->connections) {
			connection_invoker::invoke(conn, std::forward<Args>(args)...);
		}
	}

	/*!
	 * Emit signal.
	 * \see emit()
	 */
	void operator()(Args&&...args)
	{
		emit(std::forward<Args>(args)...);
	}
};
} // namespace v2
} // namespace signals
} // namespace aw
#endif//aw_signals_signal_h
