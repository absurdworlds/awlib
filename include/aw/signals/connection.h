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

template<class threading_policy>
struct connection {
	using signal_type = signal_base<threading_policy>;
	using signal_impl = signal_impl<threading_policy>;
	using observer_type = observer<threading_policy>;

	virtual ~connection() = default;

	void disconnect();

	signal_type& signal() const;

	observer_type& target() const
	{
		return *receiver;
	}

protected:
	connection(signal_impl* impl, observer_type& obj)
		: sender(impl), receiver(&obj)
	{}

	signal_impl* sender_impl() const
	{
		return sender;
	}

private:
	signal_impl* sender;
	observer_type* receiver;
};
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_connection_h
