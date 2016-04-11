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

template<class threading_policy, class signature>
struct signal;

template<class threading_policy>
struct connection {
	using observer_type = observer<threading_policy>;

	connection(observer_type& obj)
		: receiver(&obj)
	{}

	virtual void disconnect() = 0;

	/*
	signal<threading_policy>& signal() const
	{
		return *sender;
	}
	*/

	observer_type& target() const
	{
		return *receiver;
	}

private:
	//signal<threading_policy>* sender;
	observer_type* receiver;
};
} // namespace v1
} // namespace impl
} // namespace signals
} // namespace aw
#endif//aw_signals_connection_h
